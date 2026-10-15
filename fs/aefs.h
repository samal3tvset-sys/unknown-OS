#ifndef UNKNOWNOS_AEFS_H
#define UNKNOWNOS_AEFS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
const aefs_superblock_t *superblock
);

aefs_status_t aefs_mount(
aefs_volume_t *volume,
const aefs_superblock_t *superblock
);

bool aefs_is_mounted(const aefs_volume_t *volume);

void aefs_unmount(aefs_volume_t *volume);

#endif