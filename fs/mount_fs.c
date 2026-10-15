#include "fs.h"

static struct {
aefs_volume_t volume;
fs_mount_state_t state;
} root_fs = {
.state = FS_MOUNT_UNINITIALIZED
};

bool fs_mount_init(void)
{
if (root_fs.state != FS_MOUNT_UNINITIALIZED) {
return false;
}

root_fs.state = FS_MOUNT_READY;
return true;

}

bool fs_mount_root(const aefs_superblock_t *superblock)
{
if (root_fs.state != FS_MOUNT_READY ||
superblock == 0) {
return false;
}

aefs_status_t status =
    aefs_mount(&root_fs.volume, superblock);

if (status != AEFS_OK) {
    root_fs.state = FS_MOUNT_ERROR;
    return false;
}

root_fs.state = FS_MOUNT_ACTIVE;
return true;

}

bool fs_root_is_mounted(void)
{
return root_fs.state == FS_MOUNT_ACTIVE &&
aefs_is_mounted(&root_fs.volume);
}

void fs_unmount_root(void)
{
if (root_fs.state != FS_MOUNT_ACTIVE) {
return;
}

aefs_unmount(&root_fs.volume);
root_fs.state = FS_MOUNT_READY;

}

fs_mount_state_t fs_mount_get_state(void)
{
return root_fs.state;
}