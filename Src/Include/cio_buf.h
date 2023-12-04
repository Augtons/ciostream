#ifndef CIOSTREAM_CIO_BUF_H
#define CIOSTREAM_CIO_BUF_H

#include "cio.h"
#include "cio_ringbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cio_buf_istream cio_buf_istream_t;
typedef struct cio_buf_ostream cio_buf_ostream_t;

typedef struct cio_buf_istream_config cio_buf_istream_config_t;
typedef struct cio_buf_ostream_config cio_buf_ostream_config_t;

typedef size_t (*cio_buf_read_func_t)(cio_buf_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout);
typedef size_t (*cio_buf_write_func_t)(cio_buf_ostream_t *self, const uint8_t *buf, size_t len, cio_time_t timeout);

struct cio_buf_istream_config {
    uint8_t *buffer;
    uint8_t buffer_size;
    cio_buf_read_func_t on_read_func;
};

struct cio_buf_ostream_config {
    uint8_t *buffer;
    uint8_t buffer_size;
    cio_buf_write_func_t on_write_func;
};

struct cio_buf_istream {
    cio_istream_t istream;
    uint8_t *buffer;
    uint8_t buffer_size;
    cio_rb_t ringbuffer;
    cio_buf_read_func_t cio_buf_on_read_func;
};

struct cio_buf_ostream {
    cio_ostream_t ostream;
    uint8_t *buffer;
    uint8_t buffer_size;
    cio_rb_t ringbuffer;
    cio_buf_write_func_t cio_buf_on_write_func;
};

cio_err_t cio_buf_istream_init(cio_buf_istream_t *istream, cio_buf_istream_config_t *config);
cio_err_t cio_buf_ostream_init(cio_buf_ostream_t *ostream, cio_buf_ostream_config_t *config);

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_BUF_H
