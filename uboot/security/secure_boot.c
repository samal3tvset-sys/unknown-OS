#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define SECURE_BOOT_ENABLED 1
#define BOOT_KEY "123456789"

typedef enum {
    SECURE_BOOT_OK = 0,
    SECURE_BOOT_INVALID_IMAGE,
    SECURE_BOOT_INVALID_KEY,
    SECURE_BOOT_ERROR
} secure_boot_status_t;

typedef struct {
    const uint8_t *image;
    size_t image_size;
    const char *key;
} secure_boot_image_t;

static int validate_image(const secure_boot_image_t *image)
{
    if (image == NULL)
        return 0;

    if (image->image == NULL || image->image_size == 0)
        return 0;

    if (image->key == NULL)
        return 0;

    return 1;
}

secure_boot_status_t secure_boot_verify(
    const secure_boot_image_t *image
)
{
#if SECURE_BOOT_ENABLED

    if (!validate_image(image))
        return SECURE_BOOT_INVALID_IMAGE;

    if (strcmp(image->key, BOOT_KEY) != 0)
        return SECURE_BOOT_INVALID_KEY;

    return SECURE_BOOT_OK;

#else

    (void)image;

    return SECURE_BOOT_ERROR;

#endif
}
