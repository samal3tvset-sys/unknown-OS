.global _start
.extern kernel_main

.section .text.boot
_start:
mrs x0, mpidr_el1
and x0, x0, #0xFF
cbnz x0, secondary_holding_pen

ldr x1, =_stack_top
mov sp, x1

ldr x1, =__bss_start
ldr x2, =__bss_end


1:  cmp x1, x2
b.ge 2f
str xzr, [x1], #8
b 1b

2:
bl kernel_main

hang:
wfe
b hang

secondary_holding_pen:
wfe
b secondary_holding_pen

.section .bss
.align 4
.space 16384
_stack_top:
