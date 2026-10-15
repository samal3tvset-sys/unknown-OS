#ifndef UNKNOWNOS_FS_H
#define UNKNOWNOS_FS_H

#include <stdbool.h>

#include "aefs.h"

typedef enum {
FS_MOUNT_UNINITIALIZED = 0,
FS_MOUNT_READY,
FS_MOUNT_ACTIVE,
FS_MOUNT_ERROR
} fs_mount_state_t;

bool fs_mount_init(void);
bool fs_mount_root(const aefs_superblock_t *superblock);
bool fs_root_is_mounted(void);
void fs_unmount_root(void);
fs_mount_state_t fs_mount_get_state(void);

#endif