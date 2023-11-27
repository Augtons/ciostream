#include "cio_wrap.h"

static cio_err_t cio_wrap_istream_open_func(cio_istream_t *self)
{
    return CIO_OK;
}

static cio_err_t cio_wrap_ostream_open_func(cio_ostream_t *self)
{
    return CIO_OK;
}

static cio_err_t cio_wrap_istream_close_func(cio_istream_t *self)
{
    return CIO_OK;
}

static cio_err_t cio_wrap_ostream_close_func(cio_ostream_t *self)
{
    return CIO_OK;
}

static size_t cio_wrap_read_func(cio_istream_t *self, uint8_t *buf, size_t len, size_t timeout)
{
    cio_wrap_istream_t *wrap_is = CIO_CONTAINER_OF(self, cio_wrap_istream_t, istream);
    return wrap_is->cio_wrap_on_read_func(wrap_is, buf, len, timeout);
}

static size_t cio_wrap_write_func(cio_ostream_t *self, const uint8_t *buf, size_t len, size_t timeout)
{
    cio_wrap_ostream_t *wrap_os = CIO_CONTAINER_OF(self, cio_wrap_ostream_t, ostream);
    return wrap_os->cio_wrap_on_write_func(wrap_os, buf, len, timeout);
}

cio_err_t cio_wrap_istream_init(cio_wrap_istream_t *istream, cio_wrap_read_func_t on_read_func)
{
    istream->istream.cio_open = cio_wrap_istream_open_func;
    istream->istream.cio_close = cio_wrap_istream_close_func;
    istream->istream.cio_read_func = cio_wrap_read_func;

    istream->cio_wrap_on_read_func = on_read_func;

    return CIO_OK;
}

cio_err_t cio_wrap_ostream_init(cio_wrap_ostream_t *ostream, cio_wrap_write_func_t on_write_func)
{
    ostream->ostream.cio_open = cio_wrap_ostream_open_func;
    ostream->ostream.cio_close = cio_wrap_ostream_close_func;
    ostream->ostream.cio_write_func = cio_wrap_write_func;

    ostream->cio_wrap_on_write_func = on_write_func;

    return CIO_OK;
}
