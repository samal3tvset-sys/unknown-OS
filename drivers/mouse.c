#include <stdint.h>
#include <stdbool.h>

#define MOUSE_DATA_PORT 0x60
#define MOUSE_STATUS_PORT 0x64
#define MOUSE_COMMAND_PORT 0x64

#define MOUSE_STATUS_OUTPUT_FULL 0x01
#define MOUSE_STATUS_INPUT_FULL 0x02

#define MOUSE_COMMAND_ENABLE_AUX 0xA8
#define MOUSE_COMMAND_READ_CONFIG 0x20
#define MOUSE_COMMAND_WRITE_CONFIG 0x60
#define MOUSE_COMMAND_WRITE_AUX 0xD4

#define MOUSE_DEVICE_ENABLE 0xF4

typedef struct {
int32_t x;
int32_t y;
bool left_button;
bool right_button;
bool middle_button;
} mouse_state_t;

static mouse_state_t mouse_state;

static uint8_t mouse_packet[3];
static uint8_t mouse_cycle;

static inline uint8_t inb(uint16_t port)
{
uint8_t value;

__asm__ volatile (
    "inb %1, %0"
    : "=a"(value)
    : "Nd"(port)
);

return value;

}

static inline void outb(uint16_t port, uint8_t value)
{
asm volatile (
"outb %0, %1"
:
: "a"(value), "Nd"(port)
);
}

static bool mouse_wait_input(void)
{
uint32_t timeout = 100000;

while (timeout--) {
    if (!(inb(MOUSE_STATUS_PORT) & MOUSE_STATUS_INPUT_FULL))
        return true;
}

return false;

}

static bool mouse_wait_output(void)
{
uint32_t timeout = 100000;

while (timeout--) {
    if (inb(MOUSE_STATUS_PORT) & MOUSE_STATUS_OUTPUT_FULL)
        return true;
}

return false;

}

static bool mouse_write(uint8_t value)
{
if (!mouse_wait_input())
return false;

outb(MOUSE_COMMAND_PORT, MOUSE_COMMAND_WRITE_AUX);

if (!mouse_wait_input())
    return false;

outb(MOUSE_DATA_PORT, value);

return true;

}

static bool mouse_read_ack(void)
{
if (!mouse_wait_output())
return false;

return inb(MOUSE_DATA_PORT) == 0xFA;

}

bool mouse_init(void)
{
uint8_t config;

mouse_state.x = 0;
mouse_state.y = 0;
mouse_state.left_button = false;
mouse_state.right_button = false;
mouse_state.middle_button = false;

mouse_cycle = 0;

if (!mouse_wait_input())
    return false;

outb(MOUSE_COMMAND_PORT, MOUSE_COMMAND_ENABLE_AUX);

if (!mouse_wait_input())
    return false;

outb(MOUSE_COMMAND_PORT, MOUSE_COMMAND_READ_CONFIG);

if (!mouse_wait_output())
    return false;

config = inb(MOUSE_DATA_PORT);
config |= 0x02;
config &= (uint8_t)~0x20;

if (!mouse_wait_input())
    return false;

outb(MOUSE_COMMAND_PORT, MOUSE_COMMAND_WRITE_CONFIG);

if (!mouse_wait_input())
    return false;

outb(MOUSE_DATA_PORT, config);

if (!mouse_write(MOUSE_DEVICE_ENABLE))
    return false;

if (!mouse_read_ack())
    return false;

return true;

}

bool mouse_poll(void)
{
uint8_t status;
uint8_t value;
int16_t delta_x;
int16_t delta_y;

status = inb(MOUSE_STATUS_PORT);

if (!(status & MOUSE_STATUS_OUTPUT_FULL))
    return false;

if (!(status & 0x20))
    return false;

value = inb(MOUSE_DATA_PORT);

if (mouse_cycle == 0 && !(value & 0x08))
    return false;

mouse_packet[mouse_cycle++] = value;

if (mouse_cycle < 3)
    return false;

mouse_cycle = 0;

if (mouse_packet[0] & 0xC0)
    return false;

mouse_state.left_button = (mouse_packet[0] & 0x01) != 0;
mouse_state.right_button = (mouse_packet[0] & 0x02) != 0;
mouse_state.middle_button = (mouse_packet[0] & 0x04) != 0;

delta_x = (int8_t)mouse_packet[1];
delta_y = (int8_t)mouse_packet[2];

mouse_state.x += delta_x;
mouse_state.y -= delta_y;

return true;

}

mouse_state_t mouse_get_state(void)
{
return mouse_state;
}