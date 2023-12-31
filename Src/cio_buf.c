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
    cio_bool_t need_wait = (timeout != 0);
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

    uint8_t number_of_reads = 0;
    cio_time_t remain_time = timeout_time - cio_system_timestamp();

    while (number_of_reads == 0 || (need_wait && remain_time > 0)) {
        ++number_of_reads;
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
    istream->istream.user_data = config->user_data;

    istream->buffer = config->buffer;
    istream->buffer_size = config->buffer_size;
    istream->cio_buf_on_read_func = config->on_read_func;

    return cio_rb_init(&istream->ringbuffer, istream->buffer, istream->buffer_size);
}

size_t cio_buf_istream_readline(cio_istream_t *buf_istream, uint8_t *buf, size_t max_len, cio_time_t timeout)
{
    cio_buf_istream_t *istream = CIO_CONTAINER_OF(buf_istream, cio_buf_istream_t , istream);

    cio_bool_t need_wait = (timeout != 0);
    cio_time_t timeout_time = cio_system_timestamp() + timeout;

    if (buf == NULL) {
        return 0;
    }
    size_t current = cio_rb_length(&istream->ringbuffer);
    if (current >= max_len) {
        return cio_rb_read(&istream->ringbuffer, buf, max_len);
    }

    size_t write_size = 0;
    uint8_t *target_buf = buf;
    size_t rest_len = max_len;

    uint8_t temp = 0;
    cio_time_t remain_time = timeout_time - cio_system_timestamp();

    uint8_t number_of_reads = 0;

    while (rest_len != 0) {
        size_t size = cio_rb_read(&istream->ringbuffer, &temp, 1);
        if (size == 0) {
            if (number_of_reads == 0 || (need_wait && remain_time > 0)) {
                ++number_of_reads;
                size_t restore_size = istream->cio_buf_on_read_func(istream, istream->buffer, istream->buffer_size, remain_time);
                cio_rb_restore(&istream->ringbuffer, restore_size);
            } else {
                return write_size;
            }
            remain_time = timeout_time - cio_system_timestamp();
            continue;
        }

        *target_buf = temp;
        ++write_size;
        ++target_buf;
        --rest_len;
        if (temp == '\n') {
            break;
        }
    }

    return write_size;
}

/***** ostream method ******/
cio_err_t cio_buf_ostream_init(cio_buf_ostream_t *ostream, cio_buf_ostream_config_t *config)
{
    ostream->ostream.cio_close = cio_buf_ostream_close_func;
    ostream->ostream.cio_write_func = cio_buf_write_func;
    ostream->ostream.user_data = config->user_data;

    ostream->buffer = config->buffer;
    ostream->buffer_size = config->buffer_size;
    ostream->cio_buf_on_write_func = config->on_write_func;

    return cio_rb_init(&ostream->ringbuffer, ostream->buffer, ostream->buffer_size);
}
