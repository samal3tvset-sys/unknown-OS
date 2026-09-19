typedef unsigned long long u64;

void exception_handler(void) {
    while(1);
}

void kernel_main(void) {
    char *message = "UNKNOWN OS BOOTED";
    
    while(1) {
        __asm__ volatile("wfi");
    }
}
