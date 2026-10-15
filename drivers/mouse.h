#ifndef UNKNOWNOS_MOUSE_H
#define UNKNOWNOS_MOUSE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
int32_t x;
int32_t y;
bool left_button;
bool right_button;
bool middle_button;
} mouse_state_t;

bool mouse_init(void);
bool mouse_poll(void);
mouse_state_t mouse_get_state(void);

#endif