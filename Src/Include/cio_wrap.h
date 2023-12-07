#ifndef CIOSTREAM_CIO_WRAP_H
#define CIOSTREAM_CIO_WRAP_H

#include "cio.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cio_wrap_istream cio_wrap_istream_t;
typedef struct cio_wrap_ostream cio_wrap_ostream_t;

typedef struct cio_wrap_istream_config cio_wrap_istream_config_t;
typedef struct cio_wrap_ostream_config cio_wrap_ostream_config_t;

/**
 * @brief Read callback function.
 *
 * @param[in] self: WrapInputStream handle
 * @param[out] buf: Read buffer
 * @param[in] len: Length to read
 * @param[in] timeout: timeout
 * @return Length of data was read
 */
typedef size_t (*cio_wrap_read_func_t)(cio_wrap_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout);

/**
 * @brief Write callback function.
 *
 * @param self: WrapOutputStream handle
 * @param buf: Write buffer
 * @param len: Length to write
 * @param timeout: timeout
 * @return Length of data was written
 */
typedef size_t (*cio_wrap_write_func_t)(cio_wrap_ostream_t *self, const uint8_t *buf, size_t len, cio_time_t timeout);

/**
 * @brief WrapInputStream configuration.
 */
struct cio_wrap_istream_config {
    void *user_data; ///< User data
    cio_wrap_read_func_t on_read_func; ///< Read callback function pointer.
};

/**
 * @brief WrapOutputStream configuration.
 */
struct cio_wrap_ostream_config {
    void *user_data; ///< User data
    cio_wrap_write_func_t on_write_func; ///< Write callback function pointer.
};

/**
 * @brief WrapInputStream Structure.
 *
 * This structure defines a WrapInputStream that just wraps the implementation of read.
 */
struct cio_wrap_istream {
    cio_istream_t istream; ///< Base class.
    cio_wrap_read_func_t cio_wrap_on_read_func; ///< Read callback function pointer.
};

/**
 * @brief WrapOutputStream Structure.
 *
 * This structure defines a WrapOutputStream that just wraps the implementation of write.
 */
struct cio_wrap_ostream {
    cio_ostream_t ostream; ///< Base class.
    cio_wrap_write_func_t cio_wrap_on_write_func; ///< Write callback function pointer.
};

/**
 * @brief Initialize a WrapInputStream.
 *
 * This function initializes a WrapInputStream with a given configuration.
 *
 * @param istream: WrapInputStream object pointer to initialize.
 * @param config: configuration
 * @return Successfully or not
 *  - CIO_OK: Successfully
 */
cio_err_t cio_wrap_istream_init(cio_wrap_istream_t *istream, cio_wrap_istream_config_t *config);

/**
 * @brief Initialize a WrapOutputStream.
 *
 * This function initializes a WrapOutputStream with a given configuration.
 *
 * @param ostream: WrapOutputStream object pointer to initialize.
 * @param config: configuration
 * @return Successfully or not
 *  - CIO_OK: Successfully
 */
cio_err_t cio_wrap_ostream_init(cio_wrap_ostream_t *ostream, cio_wrap_ostream_config_t *config);

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_WRAP_H
