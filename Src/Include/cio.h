#ifndef CIOSTREAM_CIO_H
#define CIOSTREAM_CIO_H

#include "cio_port.h"

#ifdef __cplusplus
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

/* Error codes */
typedef enum cio_err {
    CIO_OK,
    CIO_ERR_INVALID_ARGS
} cio_err_t;

typedef struct cio_istream cio_istream_t;
typedef struct cio_ostream cio_ostream_t;
typedef struct cio_timeout_keeper cio_timeout_keeper_t;

/**
 * @brief InputStream base class
 */
struct cio_istream {
    void* user_data; ///< User data.
    cio_err_t (*cio_close)(struct cio_istream *self); ///< Close callback function pointer.
    size_t (*cio_read_func)(struct cio_istream *self, uint8_t *buf, size_t len, cio_time_t timeout); ///< Read callback function pointer.
};

/**
 * @brief OutputStream base class
 */
struct cio_ostream {
    void* user_data; ///< User data.
    cio_err_t (*cio_close)(struct cio_ostream *self); ///< Close callback function pointer.
    size_t (*cio_write_func)(struct cio_ostream *self, const uint8_t *buf, size_t len, cio_time_t timeout); ///< Write callback function pointer.
};

struct cio_timeout_keeper {
    cio_time_t start_time;
    cio_time_t wait_time;
};

#define CIO_TIMEOUT_KEEPER(wait_time)  { cio_system_timestamp(), (wait_time) }

/**
 * @brief Close an InputStream
 *
 * @param self: The pointer to the InputStream structure
 * @return Successfully or not
 *  - CIO_OK: Successfully
 */
cio_err_t cio_istream_close(struct cio_istream *self);

/**
 * @brief Close an OutputStream
 *
 * @param self: The pointer to the OutputStream structure
 * @return Successfully or not
 *  - CIO_OK: Successfully
 */
cio_err_t cio_ostream_close(struct cio_ostream *self);

/**
 * @brief Reads data from an InputStream.
 *
 * This function reads data from an InputStream
 *
 * @param[in] self: The pointer to the InputStream structure
 * @param[out] buf: Buffer
 * @param[in] len: Length to read
 * @param[in] timeout: Timeout
 * @return The actual number of bytes that were read
 */
size_t cio_read(cio_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout);

/**
 * @brief Write data to an OutputStream.
 *
 * This function writes data to an OutputStream
 *
 * @param self: The pointer to the OutputStream structure
 * @param buf: Buffer
 * @param len: Length to write
 * @param timeout: Timeout
 * @return The actual number of bytes that were write
 */
size_t cio_write(cio_ostream_t *self, const uint8_t *buf, size_t len, cio_time_t timeout);

cio_bool_t cio_timeout_check(cio_timeout_keeper_t *keeper);

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_H
