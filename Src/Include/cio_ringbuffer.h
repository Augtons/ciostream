#ifndef CIOSTREAM_CIO_RINGBUFFER_H
#define CIOSTREAM_CIO_RINGBUFFER_H

#include "cio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Ring buffer structure
 *
 * This structure defines a ring buffer that can store bytes in a circular manner.
 * It has a fixed size and two pointers (head and tail) to indicate the current status of the buffer.
 * The buffer can be used for FIFO (first-in first-out) operations, such as reading and writing data streams.
 */
struct cio_rb {
    size_t buffer_size; ///< The total size of the buffer in bytes
    size_t length; ///< The current length of the data stored in the buffer in bytes
    size_t available_length; ///< The current available space in the buffer in bytes
    uint8_t *buffer; ///< The pointer to the buffer array
    uint8_t head; ///< The head pointer, pointing to the next readable position
    uint8_t tail; ///< The tail pointer, pointing to the next writable position
};

typedef struct cio_rb cio_rb_t;

/**
 * @brief Initialize a ring buffer
 *
 * This function initializes a ring buffer with a given buffer array and size.
 * It sets the head and tail pointers to zero, and clears the buffer content.
 * The buffer array must be allocated BY THE CALLER and must not be NULL.
 * The buffer size must be positive and must not exceed the size of the buffer array.
 *
 * @param self The pointer to the ring buffer structure
 * @param buffer The pointer to the buffer array
 * @param buffer_size The size of the buffer array in bytes
 * @return Successfully or not
 *  - CIO_OK: Successfully
 *  - CIO_ERR_INVALID_ARGS: Invalid arguments
 */
cio_err_t cio_rb_init(cio_rb_t *self, uint8_t *buffer, size_t buffer_size);

/**
 * @brief Get the length of the data stored in the ring buffer
 *
 * This function returns the current length of the data stored in the ring buffer in bytes.
 *
 * @param self The pointer to the ring buffer structure
 * @return The length of the data stored in the ring buffer in bytes
 */
size_t cio_rb_length(cio_rb_t *self);

/**
 * @brief Get the available space in the ring buffer
 *
 * This function returns the current available space in the ring buffer in bytes.
 * It is equal to the buffer size minus the length of the data stored in the buffer.
 *
 * @param self The pointer to the ring buffer structure
 * @return The available space in the ring buffer in bytes
 */
size_t cio_rb_available_length(cio_rb_t *self);

/**
 * @brief Clear the ring buffer
 *
 * This function clears the ring buffer by setting the head and tail pointers to zero.
 * It does not fill the buffer array with zero bytes for performance reasons,
 * but makes the data unreadable and overwrites it on the next write operation.
 *
 * @param self The pointer to the ring buffer structure
 */
void cio_rb_clear(cio_rb_t *self);

/**
 * @brief Read data from the ring buffer
 *
 * This function reads data from the ring buffer and copies it to a given buffer array.
 * It takes the length of the buffer array as a parameter, and returns the actual number of bytes that were read from the ring buffer.
 * The function does not modify the content of the ring buffer for performance reasons, only the head pointer.
 *
 * @param self The pointer to the ring buffer structure
 * @param buf The pointer to the buffer array
 * @param len The length of the buffer array in bytes
 * @return The actual number of bytes that were read from the ring buffer
 */
size_t cio_rb_read(cio_rb_t *self, uint8_t *buf, size_t len);

/**
 * @brief Write data to the ring buffer
 *
 * This function writes data to the ring buffer from a given buffer array.
 * It takes the length of the buffer array as a parameter, and returns the actual number of bytes that were written to the ring buffer.
 *
 * @param self The pointer to the ring buffer structure
 * @param buf The pointer to the buffer array
 * @param len The length of the buffer array in bytes
 * @return The actual number of bytes that were written to the ring buffer
 */
size_t cio_rb_write(cio_rb_t *self, const uint8_t *buf, size_t len);

/**
 * @brief Restore some of data in its buffer.
 *
 * Restore some data at the start of its buffer.
 *
 * @note This a dangerous operation.
 * @param self The pointer to the ring buffer structure
 * @param len Length of data to restore.
 */
void cio_rb_restore(cio_rb_t *self, size_t len);

/**
 * @brief Skip and discard some data in its buffer.
 *
 * @param self The pointer to the ring buffer structure
 */
size_t cio_rb_skip(cio_rb_t *self, size_t len);

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_RINGBUFFER_H
