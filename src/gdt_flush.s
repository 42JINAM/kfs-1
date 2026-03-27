global gdt_flush

gdt_flush:
    mov eax, [esp+4]    ; esp+4 = argument: &gp
    lgdt [eax]          ; load GDT

    ; Reload data segment registers
    mov ax, 0x10        ; kernel data selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ax, 0x18        ; kernel data selector
    mov ss, ax

    ; Reload code segment (CS) with far jump
    jmp 0x08:.flush
    ; jmp selector:offset

.flush:
    ret
