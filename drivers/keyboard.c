#include <stdint.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define KEYBOARD_STATUS_OUTPUT_FULL 0x01
#define KEYBOARD_STATUS_INPUT_FULL 0x02

#define KEYBOARD_RELEASE_CODE 0x80

static const char keyboard_map[128] = {
0, 27, '1', '2', '3', '4', '5', '6',
'7', '8', '9', '0', '-', '=', '\b', '\t',
'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
'o', 'p', '[', ']', '\n', 0, 'a', 's',
'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
''', '`', 0, '\', 'z', 'x', 'c', 'v',
'b', 'n', 'm', ',', '.', '/', 0, '*',
0, ' '
};

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

int keyboard_has_data(void)
{
return (inb(KEYBOARD_STATUS_PORT)
& KEYBOARD_STATUS_OUTPUT_FULL) != 0;
}

char keyboard_read_char(void)
{
uint8_t scancode;

if (!keyboard_has_data())
    return 0;

scancode = inb(KEYBOARD_DATA_PORT);

if (scancode & KEYBOARD_RELEASE_CODE)
    return 0;

if (scancode >= sizeof(keyboard_map))
    return 0;

return keyboard_map[scancode];

}