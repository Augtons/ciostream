#include <stdio.h>
#include <string.h>
#include "cio_ringbuffer.h"

int main()
{
    uint8_t buf[16] = {0};

    cio_rb_t rb;
    cio_rb_init(&rb, buf, sizeof(buf));

    for (int i = 0; i < 10; ++i) {
        printf("--------------------------------\n");
        printf("Test %d:\n", i + 1);

        size_t write_size = 0;
        uint8_t write_buf[7] = "Hello!";

        do {
            write_size = cio_rb_write(&rb, write_buf, sizeof(write_buf) - 1);
            printf("%zu data written! rb.len = %zu; rb.available = %zu\n",
                   write_size, cio_rb_length(&rb), cio_rb_available_length(&rb));
        } while (write_size == sizeof(write_buf) - 1);

        size_t read_size = 0;
        uint8_t read_buf[7] = {0};

        do {
            read_size = cio_rb_read(&rb, read_buf, sizeof(read_buf) - 1);
            printf("%zu data read! rb.len = %zu; rb.available = %zu\n",
                   read_size, cio_rb_length(&rb), cio_rb_available_length(&rb));
            printf("Read data: %s\n", (char*)read_buf);
            memset(read_buf, 0, sizeof(read_buf));
        } while (read_size == sizeof(read_buf) - 1);
    }

    return 0;
}
