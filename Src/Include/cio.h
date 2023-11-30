#ifndef CIOSTREAM_CIO_H
#define CIOSTREAM_CIO_H

#if __cplusplus
    #include <cstdint>
#else
    #include <stdint.h>
#endif

#define CIO_VERSION_MAJOR   0
#define CIO_VERSION_MINOR   0
#define CIO_VERSION_PATCH   1

#define CIO_VERSION_VAL(major, minor, patch)      ((major) << 16 | (minor) << 8 | patch)
#define CIO_VERSION_STR_VAL(major, minor, patch)  (#major "." #minor "." #patch)

#define CIO_VERSION      CIO_VERSION_VAL(CIO_VERSION_MAJOR, CIO_VERSION_MINOR, CIO_VERSION_PATCH)
#define CIO_VERSION_STR  CIO_VERSION_STR_VAL(CIO_VERSION_MAJOR, CIO_VERSION_MINOR, CIO_VERSION_PATCH)

#define CIO_MAX(a, b) ((a) > (b) ? (a) : (b))
#define CIO_MIN(a, b) ((a) < (b) ? (a) : (b))

#define CIO_CONTAINER_OF(pointer, type, member) ((type*)(((char*)(pointer)) - (char*)(&(((type*)0)->member))))

#ifdef __cplusplus
extern "C" {
#endif

typedef enum cio_err {
    CIO_OK
} cio_err_t;

typedef struct cio_istream cio_istream_t;
typedef struct cio_ostream cio_ostream_t;

struct cio_istream {
    cio_err_t (*cio_open)(struct cio_istream *self);
    cio_err_t (*cio_close)(struct cio_istream *self);
    uint8_t (*cio_is_open)(struct cio_istream *self);
    size_t (*cio_read_func)(struct cio_istream *self, uint8_t *buf, size_t len, size_t timeout);
};

struct cio_ostream {
    cio_err_t (*cio_open)(struct cio_ostream *self);
    cio_err_t (*cio_close)(struct cio_ostream *self);
    uint8_t (*cio_is_open)(struct cio_ostream *self);
    size_t (*cio_write_func)(struct cio_ostream *self, const uint8_t *buf, size_t len, size_t timeout);
};

cio_err_t cio_istream_open(struct cio_istream *self);
cio_err_t cio_istream_close(struct cio_istream *self);
uint8_t cio_istream_is_open(struct cio_istream *self);

cio_err_t cio_ostream_open(struct cio_ostream *self);
cio_err_t cio_ostream_close(struct cio_ostream *self);
uint8_t cio_ostream_is_open(struct cio_ostream *self);

size_t cio_read(cio_istream_t *self, uint8_t *buf, size_t len, size_t timeout);
size_t cio_write(cio_ostream_t *self, const uint8_t *buf, size_t len, size_t timeout);

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_H
