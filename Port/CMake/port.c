#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cio_port.h"

void cio_assert_failed(const char *expression, const char *function, const char *file, int line)
{
    fprintf(stderr, "Assert Failed!\n"
                    "  - Expression: %s\n"
                    "  - Function: %s\n"
                    "  - File: %s (line: %d)\n", expression, function, file, line);
    abort();
}

cio_time_t cio_system_timestamp()
{
    return (cio_time_t)time(NULL);
}
