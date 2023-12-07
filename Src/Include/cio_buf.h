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

/**
 * @brief Read callback function.
 *
 * @param[in] self: BufferedInputStream handle
 * @param[out] buf: Read buffer
 * @param[in] len: Length to read
 * @param[in] timeout: timeout
 * @return Length of data was read
 */
typedef size_t (*cio_buf_read_func_t)(cio_buf_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout);

/**
 * @brief Write callback function.
 *
 * @param self: BufferedOutputStream handle
 * @param buf: Write buffer
 * @param len: Length to write
 * @param timeout: timeout
 * @return Length of data was written
 */
typedef size_t (*cio_buf_write_func_t)(cio_buf_ostream_t *self, const uint8_t *buf, size_t len, cio_time_t timeout);

/**
 * @brief BufferedInputStream configuration.
 */
struct cio_buf_istream_config {
    void *user_data; ///< User data
    uint8_t *buffer; ///< Buffer
    uint8_t buffer_size; ///< Buffer size
    cio_buf_read_func_t on_read_func; ///< Read callback function
};

/**
 * @brief BufferedOutputStream configuration.
 */
struct cio_buf_ostream_config {
    void *user_data; ///< User data
    uint8_t *buffer; ///< Buffer
    uint8_t buffer_size;  ///< Buffer size
    cio_buf_write_func_t on_write_func; ///< Write callback function
};

/**
 * @brief BufferedInputStream Structure.
 *
 * This structure defines a BufferedInputStream, ability to buffer the input.
 */
struct cio_buf_istream {
    cio_istream_t istream; ///< Base class
    uint8_t *buffer; ///< Internal Buffer
    uint8_t buffer_size; ///< Internal Buffer size
    cio_rb_t ringbuffer; ///< Internal RingBuffer objecct
    cio_buf_read_func_t cio_buf_on_read_func; ///< Write callback function pointer
};

/**
 * @brief BufferedOutputStream Structure.
 *
 * This structure defines a BufferedOutputStream, ability to buffer the output.
 */
struct cio_buf_ostream {
    cio_ostream_t ostream; ///< Base class
    uint8_t *buffer; ///< Internal Buffer
    uint8_t buffer_size; ///< Internal Buffer size
    cio_rb_t ringbuffer; ///< Internal RingBuffer objecct
    cio_buf_write_func_t cio_buf_on_write_func; ///< Read callback function pointer
};

/**
 * @brief Initialize a BufferedInputStream.
 *
 * This function initializes a BufferedInputStream with a given configuration.
 *
 * @param istream: BufferedInputStream object pointer to initialize.
 * @param config: configuration
 * @return Successfully or not
 *  - CIO_OK: Successfully
 */
cio_err_t cio_buf_istream_init(cio_buf_istream_t *istream, cio_buf_istream_config_t *config);

/**
 * @brief Initialize a BufferedOutputStream.
 *
 * This function initializes a BufferedOutputStream with a given configuration.
 *
 * @param ostream: BufferedOutputStream object pointer to initialize.
 * @param config: configuration
 * @return Successfully or not
 *  - CIO_OK: Successfully
 */
cio_err_t cio_buf_ostream_init(cio_buf_ostream_t *ostream, cio_buf_ostream_config_t *config);

/**
 * @brief Reads a line of text from a BufferedInputStream.
 *
 * This function reads a line of data in BufferedOutputStream, ending with `\n`.
 *
 * @param[in] buf_istream: The pointer to the InputStream structure
 * @param[out] buf: Buffer
 * @param[in] max_len: Maximum read length
 * @param[in] timeout: Timeout
 * @return The actual number of bytes that were read
 */
size_t cio_buf_istream_readline(cio_istream_t *buf_istream, uint8_t *buf, size_t max_len, cio_time_t timeout);

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_BUF_H
