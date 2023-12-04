#include <stdio.h>
#include "cio_buf.h"

size_t my_read(cio_buf_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout);

int main()
{
    cio_buf_istream_t is_buf;

    uint8_t buf[8] = {0};

    cio_buf_istream_config_t config = {
        .buffer = buf,
        .buffer_size = 8,
        .on_read_func = my_read
    };

    cio_buf_istream_init(&is_buf, &config);

    uint8_t buf_1[32] = {0};
    cio_buf_istream_readline(&is_buf, buf_1, sizeof(buf_1) - 1, 1);
    printf("buf_1 = %s\n", buf_1);

    uint8_t buf_2[32] = {0};
    cio_buf_istream_readline(&is_buf, buf_2, sizeof(buf_2) - 1, 1);
    printf("buf_2 = %s\n", buf_2);

    uint8_t buf_3[32] = {0};
    cio_buf_istream_readline(&is_buf, buf_3, sizeof(buf_3) - 1, 1);
    printf("buf_3 = %s\n", buf_3);

    uint8_t buf_4[5] = {0};
    cio_buf_istream_readline(&is_buf, buf_4, sizeof(buf_4) - 1, 1);
    printf("buf_4 = %s\n", buf_4);

    uint8_t buf_5[12] = {0};
    cio_buf_istream_readline(&is_buf, buf_5, sizeof(buf_5) - 1, 1);
    printf("buf_5 = %s\n", buf_5);
}

size_t my_read(cio_buf_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout)
{
    static char data = 'A';

    printf("[R:%zu]", len);

    for (size_t i = 0; i < len; ++i) {
        if (data > 'N') {
            buf[i] = '\n';
            data = 'A';
        } else {
            buf[i] = data;
            data++;
        }
    }

    /* Used to simulate a timeout. */
    // size_t timeout_time = cio_system_timestamp() + 1;
    // while (cio_system_timestamp() < timeout_time);

    return len;
}
