#ifndef CIOSTREAM_CIO_WRAP_H
#define CIOSTREAM_CIO_WRAP_H

#include "cio.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cio_wrap_istream cio_wrap_istream_t;
typedef struct cio_wrap_ostream cio_wrap_ostream_t;

typedef size_t (*cio_wrap_read_func_t)(cio_wrap_istream_t *self, uint8_t *buf, size_t len, size_t timeout);
typedef size_t (*cio_wrap_write_func_t)(cio_wrap_ostream_t *self, const uint8_t *buf, size_t len, size_t timeout);

struct cio_wrap_istream {
    cio_istream_t istream;
    cio_wrap_read_func_t cio_wrap_on_read_func;
    uint8_t is_open;
};

struct cio_wrap_ostream {
    cio_ostream_t ostream;
    cio_wrap_write_func_t cio_wrap_on_write_func;
    uint8_t is_open;
};

cio_err_t cio_wrap_istream_init(cio_wrap_istream_t *istream, cio_wrap_read_func_t on_read_func);
cio_err_t cio_wrap_ostream_init(cio_wrap_ostream_t *ostream, cio_wrap_write_func_t on_write_func);

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_WRAP_H
