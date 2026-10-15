#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define KERNEL_MAGIC 0x554E4B4EU
#define KERNEL_VERSION 1U

typedef enum {
KERNEL_LOAD_OK = 0,
KERNEL_LOAD_INVALID_ARGUMENT,
KERNEL_LOAD_INVALID_MAGIC,
KERNEL_LOAD_INVALID_VERSION,
KERNEL_LOAD_INVALID_SIZE,
KERNEL_LOAD_INVALID_ENTRY
} kernel_load_status_t;

typedef struct {
uint32_t magic;
uint32_t version;
uint64_t image_size;
uint64_t entry_offset;
} kernel_header_t;

typedef struct {
const uint8_t *image;
size_t image_size;
const kernel_header_t *header;
const uint8_t *entry;
} kernel_image_t;

kernel_load_status_t kernel_load_validate(
const void *data,
size_t data_size,
kernel_image_t *result
)
{
const kernel_header_t *header;
const uint8_t *image;

if (data == NULL || result == NULL) {
    return KERNEL_LOAD_INVALID_ARGUMENT;
}

result->image = NULL;
result->image_size = 0;
result->header = NULL;
result->entry = NULL;

if (data_size < sizeof(kernel_header_t)) {
    return KERNEL_LOAD_INVALID_SIZE;
}

image = (const uint8_t *)data;
header = (const kernel_header_t *)data;

if (header->magic != KERNEL_MAGIC) {
    return KERNEL_LOAD_INVALID_MAGIC;
}

if (header->version != KERNEL_VERSION) {
    return KERNEL_LOAD_INVALID_VERSION;
}

if (header->image_size < sizeof(kernel_header_t) ||
    header->image_size > data_size ||
    header->image_size > SIZE_MAX) {
    return KERNEL_LOAD_INVALID_SIZE;
}

if (header->entry_offset < sizeof(kernel_header_t) ||
    header->entry_offset >= header->image_size) {
    return KERNEL_LOAD_INVALID_ENTRY;
}

result->image = image;
result->image_size = (size_t)header->image_size;
result->header = header;
result->entry = image + (size_t)header->entry_offset;

return KERNEL_LOAD_OK;

}