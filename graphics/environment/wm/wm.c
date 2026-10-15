#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define WM_MAX_WINDOWS 32

typedef uint32_t wm_window_id_t;

typedef enum {
WM_WINDOW_UNUSED = 0,
WM_WINDOW_HIDDEN,
WM_WINDOW_VISIBLE
} wm_window_state_t;

typedef struct {
wm_window_id_t id;
int32_t x;
int32_t y;
uint32_t width;
uint32_t height;
wm_window_state_t state;
} wm_window_t;

typedef struct {
wm_window_t windows[WM_MAX_WINDOWS];
size_t window_count;
wm_window_id_t active_window;
wm_window_id_t next_window_id;
bool initialized;
} wm_context_t;

static wm_context_t wm;

bool wm_init(void)
{
if (wm.initialized) {
return false;
}

wm.window_count = 0;
wm.active_window = 0;
wm.next_window_id = 1;
wm.initialized = true;

for (size_t i = 0; i < WM_MAX_WINDOWS; i++) {
    wm.windows[i].state = WM_WINDOW_UNUSED;
}

return true;

}

wm_window_id_t wm_create_window(
int32_t x,
int32_t y,
uint32_t width,
uint32_t height)
{
if (!wm.initialized ||
width == 0 ||
height == 0 ||
wm.window_count >= WM_MAX_WINDOWS ||
wm.next_window_id == 0) {
return 0;
}

for (size_t i = 0; i < WM_MAX_WINDOWS; i++) {
    if (wm.windows[i].state != WM_WINDOW_UNUSED) {
        continue;
    }

    wm_window_t *window = &wm.windows[i];

    window->id = wm.next_window_id++;
    window->x = x;
    window->y = y;
    window->width = width;
    window->height = height;
    window->state = WM_WINDOW_VISIBLE;

    wm.window_count++;
    wm.active_window = window->id;

    return window->id;
}

return 0;

}

bool wm_show_window(wm_window_id_t id)
{
if (!wm.initialized || id == 0) {
return false;
}

for (size_t i = 0; i < WM_MAX_WINDOWS; i++) {
    wm_window_t *window = &wm.windows[i];

    if (window->id == id &&
        window->state != WM_WINDOW_UNUSED) {
        window->state = WM_WINDOW_VISIBLE;
        wm.active_window = id;
        return true;
    }
}

return false;

}

bool wm_hide_window(wm_window_id_t id)
{
if (!wm.initialized || id == 0) {
return false;
}

for (size_t i = 0; i < WM_MAX_WINDOWS; i++) {
    wm_window_t *window = &wm.windows[i];

    if (window->id == id &&
        window->state != WM_WINDOW_UNUSED) {
        window->state = WM_WINDOW_HIDDEN;

        if (wm.active_window == id) {
            wm.active_window = 0;
        }

        return true;
    }
}

return false;

}

bool wm_move_window(
wm_window_id_t id,
int32_t x,
int32_t y)
{
if (!wm.initialized || id == 0) {
return false;
}

for (size_t i = 0; i < WM_MAX_WINDOWS; i++) {
    wm_window_t *window = &wm.windows[i];

    if (window->id == id &&
        window->state != WM_WINDOW_UNUSED) {
        window->x = x;
        window->y = y;
        return true;
    }
}

return false;

}

bool wm_resize_window(
wm_window_id_t id,
uint32_t width,
uint32_t height)
{
if (!wm.initialized ||
id == 0 ||
width == 0 ||
height == 0) {
return false;
}

for (size_t i = 0; i < WM_MAX_WINDOWS; i++) {
    wm_window_t *window = &wm.windows[i];

    if (window->id == id &&
        window->state != WM_WINDOW_UNUSED) {
        window->width = width;
        window->height = height;
        return true;
    }
}

return false;

}

bool wm_focus_window(wm_window_id_t id)
{
if (!wm.initialized || id == 0) {
return false;
}

for (size_t i = 0; i < WM_MAX_WINDOWS; i++) {
    wm_window_t *window = &wm.windows[i];

    if (window->id == id &&
        window->state == WM_WINDOW_VISIBLE) {
        wm.active_window = id;
        return true;
    }
}

return false;

}

const wm_window_t *wm_get_window(wm_window_id_t id)
{
if (!wm.initialized || id == 0) {
return NULL;
}

for (size_t i = 0; i < WM_MAX_WINDOWS; i++) {
    if (wm.windows[i].id == id &&
        wm.windows[i].state != WM_WINDOW_UNUSED) {
        return &wm.windows[i];
    }
}

return NULL;

}

wm_window_id_t wm_get_active_window(void)
{
return wm.active_window;
}

size_t wm_get_window_count(void)
{
return wm.window_count;
}