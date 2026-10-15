[BITS 16]
[ORG 0x7C00]

_start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov [boot_drive], dl

    mov si, boot_msg
    call print_string

    mov dl, [boot_drive]
    mov si, disk_packet
    mov ah, 0x42
    int 0x13
    jc disk_error

    jmp 0x0000:0x8000

disk_error:
    mov si, error_msg
    call print_string

hang:
    cli
    hlt
    jmp hang

print_string:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

boot_drive:
    db 0

boot_msg:
    db "Stage 1: Booting...", 13, 10, 0

error_msg:
    db "Disk read error!", 13, 10, 0

disk_packet:
    db 0x10, 0
    dw 32
    dw 0x8000
    dw 0
    dq 1

times 510 - ($ - $$) db 0
dw 0xAA55
