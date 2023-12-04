#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "cio_port.h"

void cio_assert(int expression, const char * function, const char * file, int line)
{
    assert(expression);
}

cio_time_t cio_system_timestamp()
{
    return (cio_time_t)time(NULL);
}