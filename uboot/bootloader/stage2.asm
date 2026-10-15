[BITS 16]
[ORG 0x8000]

stage2_start:
    cli

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov si, stage2_msg
    call print_string

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:protected_mode


[BITS 32]

protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax

    mov esp, 0x90000

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov eax, pml4_table
    mov cr3, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    jmp 0x18:long_mode


[BITS 64]

long_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax

    mov rsp, 0x90000

    mov rdi, 0xB8000
    mov rsi, long_msg

.print:
    lodsb
    test al, al
    jz .hang

    mov ah, 0x0F
    mov [rdi], ax
    add rdi, 2
    jmp .print

.hang:
    cli
    hlt
    jmp .hang


[BITS 16]

print_string:
    lodsb
    test al, al
    jz .done

    mov ah, 0x0E
    int 0x10

    jmp print_string

.done:
    ret


align 8

gdt_start:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
    dq 0x00AF9A000000FFFF

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start


align 4096

pml4_table:
    dq pdpt_table + 3
    times 511 dq 0

align 4096

pdpt_table:
    dq pd_table + 3
    times 511 dq 0

align 4096

pd_table:
    dq 0x0000000000000083
    times 511 dq 0


stage2_msg:
    db "Stage 2: Entering long mode...", 13, 10, 0

long_msg:
    db "Welcome to UnknownOS!", 0
    
