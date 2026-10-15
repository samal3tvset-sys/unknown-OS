#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define ROOT_FS_NAME "UnknownFS"

typedef enum {
ROOT_MOUNT_UNINITIALIZED = 0,
ROOT_MOUNT_READY,
ROOT_MOUNT_MOUNTED,
ROOT_MOUNT_ERROR
} root_mount_state_t;

typedef struct {
const char *name;
uint64_t device_id;
root_mount_state_t state;
} root_mount_info_t;

static root_mount_info_t root_mount = {
ROOT_FS_NAME,
0,
ROOT_MOUNT_UNINITIALIZED
};

bool mount_root_init(void)
{
if (root_mount.state != ROOT_MOUNT_UNINITIALIZED) {
return false;
}

root_mount.device_id = 0;
root_mount.state = ROOT_MOUNT_READY;

return true;

}

bool mount_root_attach(uint64_t device_id)
{
if (root_mount.state != ROOT_MOUNT_READY || device_id == 0) {
return false;
}

root_mount.device_id = device_id;

/*
 * TODO:
 * Detect the filesystem.
 * Validate filesystem metadata.
 * Mount the root filesystem through the VFS.
 */

root_mount.state = ROOT_MOUNT_ERROR;
return false;

}

bool mount_root_is_mounted(void)
{
return root_mount.state == ROOT_MOUNT_MOUNTED;
}

root_mount_info_t mount_root_get_info(void)
{
return root_mount;
}

void mount_root_reset(void)
{
if (root_mount.state != ROOT_MOUNT_MOUNTED) {
root_mount.device_id = 0;
root_mount.state = ROOT_MOUNT_UNINITIALIZED;
}
}