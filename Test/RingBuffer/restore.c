#include <string.h>
#include <stdio.h>
#include "cio_ringbuffer.h"

int main()
{
    uint8_t buf[16] = {0};

    cio_rb_t rb;
    cio_rb_init(&rb, buf, sizeof(buf));

    memcpy(buf, "ABCDEF", 6);

    cio_rb_restore(&rb, 6);

    cio_rb_skip(&rb, 3);

    uint8_t read_buf[12] = {0};
    size_t len = cio_rb_read(&rb, read_buf, sizeof(read_buf));

    printf("read len = %zu\n", len);
    printf("read data = %s\n", (char*)read_buf);

}