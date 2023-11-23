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

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif //CIOSTREAM_CIO_H
