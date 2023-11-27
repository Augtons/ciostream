#include "cio.h"

cio_err_t cio_istream_open(struct cio_istream *self)
{
    return self->cio_open(self);
}

cio_err_t cio_istream_close(struct cio_istream *self)
{
    return self->cio_close(self);
}

cio_err_t cio_ostream_open(struct cio_ostream *self)
{
    return self->cio_open(self);
}

cio_err_t cio_ostream_close(struct cio_ostream *self)
{
    return self->cio_close(self);
}

size_t cio_read(cio_istream_t *self, uint8_t *buf, size_t len, size_t timeout)
{
    return self->cio_read_func(self, buf, len, timeout);
}

size_t cio_write(cio_ostream_t *self, const uint8_t *buf, size_t len, size_t timeout)
{
    return self->cio_write_func(self, buf, len, timeout);
}
