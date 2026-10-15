#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define AEFS_MAGIC 0x53464541U
#define AEFS_VERSION 1U
#define AEFS_BLOCK_SIZE 4096U

typedef enum {
AEFS_OK = 0,
AEFS_ERROR_ARGUMENT,
AEFS_ERROR_MAGIC,
AEFS_ERROR_VERSION,
AEFS_ERROR_BLOCK_SIZE,
AEFS_ERROR_CAPACITY
} aefs_status_t;

typedef struct {
uint32_t magic;
uint32_t version;
uint32_t block_size;
uint32_t total_blocks;
uint32_t free_blocks;
} aefs_superblock_t;

typedef struct {
aefs_superblock_t superblock;
bool mounted;
} aefs_volume_t;

aefs_status_t aefs_validate_superblock(
const aefs_superblock_t *superblock)
{
if (superblock == NULL) {
return AEFS_ERROR_ARGUMENT;
}

if (superblock->magic != AEFS_MAGIC) {
    return AEFS_ERROR_MAGIC;
}

if (superblock->version != AEFS_VERSION) {
    return AEFS_ERROR_VERSION;
}

if (superblock->block_size != AEFS_BLOCK_SIZE) {
    return AEFS_ERROR_BLOCK_SIZE;
}

if (superblock->total_blocks == 0 ||
    superblock->free_blocks > superblock->total_blocks) {
    return AEFS_ERROR_CAPACITY;
}

return AEFS_OK;

}

aefs_status_t aefs_mount(
aefs_volume_t *volume,
const aefs_superblock_t *superblock)
{
if (volume == NULL || superblock == NULL) {
return AEFS_ERROR_ARGUMENT;
}

volume->mounted = false;

aefs_status_t status =
    aefs_validate_superblock(superblock);

if (status != AEFS_OK) {
    return status;
}

memcpy(&volume->superblock, superblock,
       sizeof(aefs_superblock_t));

volume->mounted = true;

return AEFS_OK;

}

bool aefs_is_mounted(const aefs_volume_t *volume)
{
return volume != NULL && volume->mounted;
}

void aefs_unmount(aefs_volume_t *volume)
{
if (volume == NULL) {
return;
}

volume->mounted = false;

}