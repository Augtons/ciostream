#ifndef CIOSTREAM_CIO_PORT_H
#define CIOSTREAM_CIO_PORT_H

#include <stdint.h>

#define CIO_ASSERT(expression)  do {                                                                  \
                                    if (!(expression)) {                                              \
                                        cio_assert_failed(#expression, __func__, __FILE__, __LINE__); \
                                    }                                                                 \
                                } while(0)

typedef int64_t cio_time_t;
typedef uint8_t cio_bool_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Port function. Show assert failed message.
 *
 * @param expression: Assert expression
 * @param function: Name of the function where assert failed.
 * @param file: Full path of the file where assert failed.
 * @param line: Line number of the position where assert failed.
 */
void cio_assert_failed(const char *expression, const char *function, const char *file, int line);

/**
 * @brief Port function. Get system timestamp
 *
 * @note The unit of the timestamp is implementation defined.
 *       It determines the unit of the timeout parameter for all of cio api functions.
 *
 * @return Timestamp.
 */
cio_time_t cio_system_timestamp();

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_PORT_H
