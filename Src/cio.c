#include "cio.h"

cio_err_t cio_istream_close(struct cio_istream *self)
{
    return self->cio_close(self);
}

cio_err_t cio_ostream_close(struct cio_ostream *self)
{
    return self->cio_close(self);
}

size_t cio_read(cio_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout)
{
    return self->cio_read_func(self, buf, len, timeout);
}

size_t cio_write(cio_ostream_t *self, const uint8_t *buf, size_t len, cio_time_t timeout)
{
    return self->cio_write_func(self, buf, len, timeout);
}

cio_bool_t cio_timeout_check(cio_timeout_keeper_t *keeper)
{
    return cio_system_timestamp() - keeper->start_time > keeper->wait_time;
}
