#ifndef CIOSTREAM_CIO_PORT_H
#define CIOSTREAM_CIO_PORT_H

#include <stdint.h>

#define CIO_ASSERT(expression) cio_assert(expression, __func__, __FILE__, __LINE__);
#define cio_time_t int64_t

#ifdef __cplusplus
extern "C" {
#endif

void cio_assert(int expression, const char * function, const char * file, int line);

cio_time_t cio_system_timestamp();

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_PORT_H
