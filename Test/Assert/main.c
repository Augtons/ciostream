#include <stdio.h>
#include "cio.h"

#include <assert.h>

int main()
{
    printf("Assert Test\n");

    CIO_ASSERT(1 + 1 == 3);
}
