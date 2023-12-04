#include <string.h>
#include "cio_buf.h"

/***** istream virtual method ******/
static cio_err_t cio_buf_istream_close_func(cio_istream_t *self)
{
    cio_buf_istream_t *is_buf = CIO_CONTAINER_OF(self, cio_buf_istream_t, istream);
    return CIO_OK;
}

static size_t cio_buf_read_func(cio_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout)
{
    cio_time_t timeout_time = cio_system_timestamp() + timeout;

    if (buf == NULL) {
        return 0;
    }
    cio_buf_istream_t *is_buf = CIO_CONTAINER_OF(self, cio_buf_istream_t, istream);
    size_t current = cio_rb_length(&is_buf->ringbuffer);
    if (current >= len) {
        return cio_rb_read(&is_buf->ringbuffer, buf, len);
    }

    size_t write_size = cio_rb_read(&is_buf->ringbuffer, buf, current);

    uint8_t *target_buf = buf + write_size;
    size_t rest_len = len - write_size;

    cio_time_t remain_time = timeout_time - cio_system_timestamp();

    while (remain_time > 0) {
        if (rest_len > is_buf->buffer_size) {
            write_size += is_buf->cio_buf_on_read_func(is_buf, target_buf, is_buf->buffer_size, remain_time);
            target_buf = buf + write_size;
            rest_len = len - write_size;
        } else {
            size_t restore_size = is_buf->cio_buf_on_read_func(is_buf, is_buf->buffer, is_buf->buffer_size, remain_time);
            cio_rb_restore(&is_buf->ringbuffer, restore_size);
            write_size += cio_rb_read(&is_buf->ringbuffer, target_buf, rest_len);
            break;
        }

        remain_time = timeout_time - cio_system_timestamp();
    }

    return write_size;
}

/***** ostream virtual method ******/
static cio_err_t cio_buf_ostream_close_func(cio_ostream_t *self)
{
    cio_buf_ostream_t *os_buf = CIO_CONTAINER_OF(self, cio_buf_ostream_t, ostream);
    return CIO_OK;
}

static size_t cio_buf_write_func(cio_ostream_t *self, const uint8_t *buf, size_t len, cio_time_t timeout)
{
    return 0;
}

/***** istream method ******/
cio_err_t cio_buf_istream_init(cio_buf_istream_t *istream, cio_buf_istream_config_t *config)
{
    istream->istream.cio_close = cio_buf_istream_close_func;
    istream->istream.cio_read_func = cio_buf_read_func;

    istream->buffer = config->buffer;
    istream->buffer_size = config->buffer_size;
    istream->cio_buf_on_read_func = config->on_read_func;

    return cio_rb_init(&istream->ringbuffer, istream->buffer, istream->buffer_size);
}

/***** ostream method ******/
cio_err_t cio_buf_ostream_init(cio_buf_ostream_t *ostream, cio_buf_ostream_config_t *config)
{
    ostream->ostream.cio_close = cio_buf_ostream_close_func;
    ostream->ostream.cio_write_func = cio_buf_write_func;

    ostream->buffer = config->buffer;
    ostream->buffer_size = config->buffer_size;
    ostream->cio_buf_on_write_func = config->on_write_func;

    return cio_rb_init(&ostream->ringbuffer, ostream->buffer, ostream->buffer_size);
}
