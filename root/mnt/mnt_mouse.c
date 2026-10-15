#include <stdbool.h>
#include <stdint.h>

#include "../../drivers/mouse.h"

typedef enum {
MNT_MOUSE_UNINITIALIZED = 0,
MNT_MOUSE_READY,
MNT_MOUSE_ERROR
} mnt_mouse_status_t;

static mnt_mouse_status_t mouse_status = MNT_MOUSE_UNINITIALIZED;

bool mnt_mouse_init(void)
{
mouse_status = MNT_MOUSE_UNINITIALIZED;

if (!mouse_init()) {
    mouse_status = MNT_MOUSE_ERROR;
    return false;
}

mouse_status = MNT_MOUSE_READY;
return true;

}

bool mnt_mouse_update(void)
{
if (mouse_status != MNT_MOUSE_READY) {
return false;
}

return mouse_poll();

}

bool mnt_mouse_is_ready(void)
{
return mouse_status == MNT_MOUSE_READY;
}

bool mnt_mouse_get_position(int32_t *x, int32_t *y)
{
if (mouse_status != MNT_MOUSE_READY || x == 0 || y == 0) {
return false;
}

mouse_state_t state = mouse_get_state();

*x = state.x;
*y = state.y;

return true;

}

bool mnt_mouse_get_button(uint8_t button)
{
if (mouse_status != MNT_MOUSE_READY) {
return false;
}

mouse_state_t state = mouse_get_state();

switch (button) {
    case 1:
        return state.left_button;

    case 2:
        return state.right_button;

    case 3:
        return state.middle_button;

    default:
        return false;
}

}

void mnt_mouse_shutdown(void)
{
mouse_status = MNT_MOUSE_UNINITIALIZED;
}