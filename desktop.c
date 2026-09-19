#include "kernel.c"
#include "touchscreen.c"
#include "de.c"

void kernel_main(void) {
    uart_print("INITIALIZING DESKTOP...\n");
    desktop_init();
    touch_init();

    int x, y;
    while(1) {
        if (touch_read(&x, &y)) {
            if (x >= 60 && x <= 180 && y >= 1400 && y <= 1520) {
                uart_print("APP 1 CLICKED\n");
            }
        }
        __asm__ volatile("wfi");
    }
}
