#include "cio_ringbuffer.h"

cio_err_t cio_rb_init(cio_rb_t *self, uint8_t *buffer, size_t buffer_size)
{
    if (buffer == NULL) {
        return CIO_ERR_INVALID_ARGS;
    }

    self->buffer_size = buffer_size;
    self->buffer = buffer;

    self->length = 0;
    self->available_length = buffer_size;

    self->head = 0;
    self->tail = 0;

    return CIO_OK;
}

size_t cio_rb_length(cio_rb_t *self)
{
    return self->length;
}

size_t cio_rb_available_length(cio_rb_t *self)
{
    return self->available_length;
}

void cio_rb_clear(cio_rb_t *self)
{
    self->length = 0;
    self->available_length = self->buffer_size;
    self->head = 0;
    self->tail = 0;
}

size_t cio_rb_read(cio_rb_t *self, uint8_t * const buf, size_t len)
{
    uint8_t begin = self->head;
    uint8_t len_to_read = CIO_MIN(cio_rb_length(self), len);

    self->length -= len_to_read;
    self->head = (begin + len_to_read) % self->buffer_size;

    size_t count = 0;

    while (count < len_to_read) {
        buf[count] = self->buffer[(begin + count) % self->buffer_size];
        ++count;
    }

    self->available_length += count;

    return count;
}

size_t cio_rb_write(cio_rb_t *self, const uint8_t * const buf, size_t len)
{
    uint8_t begin = self->tail;
    uint8_t len_to_write = CIO_MIN(cio_rb_available_length(self), len);

    self->available_length -= len_to_write;
    self->tail = (begin + len_to_write) % self->buffer_size;

    size_t count = 0;

    while (count < len_to_write) {
        self->buffer[(begin + count) % self->buffer_size] = buf[count];
        ++count;
    }

    self->length += len_to_write;

    return count;
}

void cio_rb_restore(cio_rb_t *self, size_t len)
{
    self->length = len;
    self->available_length = self->buffer_size - len;
    self->head = 0;
    self->tail = 0;
}

size_t cio_rb_skip(cio_rb_t *self, size_t len)
{
    uint8_t begin = self->head;
    uint8_t len_to_skip = CIO_MIN(cio_rb_length(self), len);

    self->length -= len_to_skip;
    self->head = (begin + len_to_skip) % self->buffer_size;

    self->available_length += len_to_skip;

    return len_to_skip;
}
