#define FIMD_BASE 0x14800000

static volatile unsigned int *const VSYNC = (unsigned int *)(FIMD_BASE + 0x00);
static volatile unsigned int *const VIDCON0 = (unsigned int *)(FIMD_BASE + 0x10);
static volatile unsigned int *const VIDOSD0A = (unsigned int *)(FIMD_BASE + 0x40);

void screen_init(unsigned int *framebuffer) {
    *VIDCON0 |= (1 << 0);
    *VIDOSD0A = (unsigned int)framebuffer;
}
