#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1560
#define FB_BASE 0xE0000000

void draw_pixel(int x, int y, unsigned int color) {
    volatile unsigned int *fb = (unsigned int *)FB_BASE;
    fb[y * SCREEN_WIDTH + x] = color;
}

void draw_rect(int x, int y, int w, int h, unsigned int color) {
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            draw_pixel(j, i, color);
        }
    }
}

void desktop_init(void) {
    draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x001E1E1E);
    draw_rect(0, 0, SCREEN_WIDTH, 80, 0x002D2D2D);
    draw_rect(60, 1400, 120, 120, 0x00007ACC);
    draw_rect(220, 1400, 120, 120, 0x00388A34);
    draw_rect(380, 1400, 120, 120, 0x00CE9178);
    draw_rect(540, 1400, 120, 120, 0x00D16969);
}
