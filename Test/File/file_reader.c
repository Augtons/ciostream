#include <stdio.h>
#include <errno.h>
#include "cio_buf.h"

size_t my_file_read(cio_buf_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout);

int main()
{
    FILE *file = fopen(__FILE__, "r");
    if (file == NULL) {
        return errno;
    }

    cio_buf_istream_t in;

    uint8_t buffer[128] = {0};
    cio_buf_istream_config_t config = {
        .buffer = buffer,
        .buffer_size = sizeof(buffer),
        .on_read_func = my_file_read,
        .user_data = file
    };

    cio_buf_istream_init(&in, &config);

    size_t read_len;
    do {
        uint8_t read_buffer[256] = {0};
        read_len = cio_buf_istream_readline(&in.istream, read_buffer, sizeof(read_buffer), 0);
        printf("%.*s", (int)read_len, read_buffer);
    } while (read_len != 0);

    fclose(file);
}

size_t my_file_read(cio_buf_istream_t *self, uint8_t *buf, size_t len, cio_time_t timeout)
{
    FILE *file = (FILE*)self->istream.user_data;
    return fread(buf, sizeof(uint8_t), len, file);
}
