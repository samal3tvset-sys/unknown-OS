#ifndef UNKNOWNOS_SCREEN_H
#define UNKNOWNOS_SCREEN_H

#include <stdint.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define SCREEN_COLOR_BLACK 0x00
#define SCREEN_COLOR_BLUE 0x01
#define SCREEN_COLOR_GREEN 0x02
#define SCREEN_COLOR_CYAN 0x03
#define SCREEN_COLOR_RED 0x04
#define SCREEN_COLOR_MAGENTA 0x05
#define SCREEN_COLOR_BROWN 0x06
#define SCREEN_COLOR_LIGHT_GREY 0x07
#define SCREEN_COLOR_DARK_GREY 0x08
#define SCREEN_COLOR_LIGHT_BLUE 0x09
#define SCREEN_COLOR_LIGHT_GREEN 0x0A
#define SCREEN_COLOR_LIGHT_CYAN 0x0B
#define SCREEN_COLOR_LIGHT_RED 0x0C
#define SCREEN_COLOR_LIGHT_MAGENTA 0x0D
#define SCREEN_COLOR_YELLOW 0x0E
#define SCREEN_COLOR_WHITE 0x0F

void screen_clear(void);
void screen_set_color(uint8_t color);
void screen_put_char(char character);
void screen_write(const char *text);

#endif