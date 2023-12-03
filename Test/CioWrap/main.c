#include <stdio.h>
#include "cio_wrap.h"

cio_wrap_ostream_t os;
cio_wrap_istream_t is;

static size_t write_to_stdout(cio_wrap_ostream_t *self, const uint8_t *buf, size_t len, size_t timeout);
static size_t read_from_stdin(cio_wrap_istream_t *self, uint8_t *buf, size_t len, size_t timeout);

int main()
{
    // 1. Make the output stream point to stdout。
    cio_wrap_ostream_config_t ostream_config;
    ostream_config.on_write_func = write_to_stdout;

    cio_wrap_ostream_init(&os, &ostream_config);

    // 2. Make the input stream point to stdin.
    cio_wrap_istream_config_t istream_config;
    istream_config.on_read_func = read_from_stdin;

    cio_wrap_istream_init(&is, &istream_config);

    // 3. Get input/output stream base object. (For Polymorphism)
    cio_ostream_t *out = &os.ostream;
    cio_istream_t *in = &is.istream;

    // 4. Define a buffer.
    uint8_t buf[] = "Hello World";

    // Test 1: This will write to console (stdout).
    cio_write(out, buf, sizeof(buf), 0);
    cio_ostream_close(out);

    // Test 2: This will read from console (stdin).
    printf("\n---\nPlease input %zu characters.\n>>> ", sizeof(buf) - 1);

    cio_read(in, buf, sizeof(buf) - 1, 0);
    cio_istream_close(in);

    printf("\n---\ndata:\n%s", buf);

    return 0;
}

static size_t write_to_stdout(cio_wrap_ostream_t *self, const uint8_t *buf, size_t len, size_t timeout)
{
    printf("%.*s", (int)len, buf);
    return len;
}

static size_t read_from_stdin(cio_wrap_istream_t *self, uint8_t *buf, size_t len, size_t timeout)
{
    for (size_t i = 0; i < len;) {
        uint8_t c = getchar();
        if (c) {
            *buf++ = c;
            ++i;
        }
    }
    return len;
}
