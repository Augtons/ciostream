#ifndef CIOSTREAM_CIO_PORT_H
#define CIOSTREAM_CIO_PORT_H

#include <stdint.h>

#define CIO_ASSERT(expression)  do {                                                                  \
                                    if (!(expression)) {                                                \
                                        cio_assert_failed(#expression, __func__, __FILE__, __LINE__); \
                                    }                                                                 \
                                } while(0)

typedef int64_t cio_time_t;

#ifdef __cplusplus
extern "C" {
#endif

void cio_assert_failed(const char *expression, const char *function, const char *file, int line);

cio_time_t cio_system_timestamp();

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_PORT_H
