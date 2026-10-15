#include <stdint.h>
#include <stddef.h>

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_COLOR_WHITE 0x0F
#define VGA_COLOR_BLACK 0x00

static volatile uint16_t *const vga_buffer =
(volatile uint16_t *)VGA_MEMORY;

static size_t cursor_x = 0;
static size_t cursor_y = 0;
static uint8_t screen_color = VGA_COLOR_WHITE;

static uint16_t vga_entry(char character, uint8_t color)
{
return (uint16_t)character | ((uint16_t)color << 8);
}

static void screen_scroll(void)
{
size_t y;
size_t x;

for (y = 1; y < VGA_HEIGHT; y++) {
    for (x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[(y - 1) * VGA_WIDTH + x] =
            vga_buffer[y * VGA_WIDTH + x];
    }
}

for (x = 0; x < VGA_WIDTH; x++) {
    vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] =
        vga_entry(' ', screen_color);
}

cursor_y = VGA_HEIGHT - 1;

}

void screen_clear(void)
{
size_t x;
size_t y;

for (y = 0; y < VGA_HEIGHT; y++) {
    for (x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[y * VGA_WIDTH + x] =
            vga_entry(' ', screen_color);
    }
}

cursor_x = 0;
cursor_y = 0;

}

void screen_set_color(uint8_t color)
{
screen_color = color;
}

void screen_put_char(char character)
{
if (character == '\n') {
cursor_x = 0;
cursor_y++;
} else if (character == '\r') {
cursor_x = 0;
} else if (character == '\b') {
if (cursor_x > 0) {
cursor_x--;
vga_buffer[cursor_y * VGA_WIDTH + cursor_x] =
vga_entry(' ', screen_color);
}
} else {
vga_buffer[cursor_y * VGA_WIDTH + cursor_x] =
vga_entry(character, screen_color);

    cursor_x++;

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
}

if (cursor_y >= VGA_HEIGHT) {
    screen_scroll();
}

}

void screen_write(const char *text)
{
size_t i = 0;

if (text == NULL) {
    return;
}

while (text[i] != '\0') {
    screen_put_char(text[i]);
    i++;
}

}