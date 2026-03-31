section .text
extern general_handler

interupt_0:
    push 0
    call general_handler
    add esp, 4
    iret

interupt_1:
    push 1
    call general_handler
    add esp, 4
    iret

interupt_2:
    push 2
    call general_handler
    add esp, 4
    iret

interupt_3:
    push 3
    call general_handler
    add esp, 4
    iret

interupt_4:
    push 4
    call general_handler
    add esp, 4
    iret

interupt_5:
    push 5
    call general_handler
    add esp, 4
    iret

interupt_6:
    push 6
    call general_handler
    add esp, 4
    iret

interupt_7:
    push 7
    call general_handler
    add esp, 4
    iret

interupt_8:
    push 8
    call general_handler
    add esp, 4
    iret

interupt_9:
    push 9
    call general_handler
    add esp, 4
    iret

interupt_10:
    push 10
    call general_handler
    add esp, 4
    iret

interupt_11:
    push 11
    call general_handler
    add esp, 4
    iret

interupt_12:
    push 12
    call general_handler
    add esp, 4
    iret

interupt_13:
    push 13
    call general_handler
    add esp, 4
    iret

interupt_14:
    push 14
    call general_handler
    add esp, 4
    iret

interupt_15:
    push 15
    call general_handler
    add esp, 4
    iret

interupt_16:
    push 16
    call general_handler
    add esp, 4
    iret

interupt_17:
    push 17
    call general_handler
    add esp, 4
    iret

interupt_18:
    push 18
    call general_handler
    add esp, 4
    iret

interupt_19:
    push 19
    call general_handler
    add esp, 4
    iret

interupt_20:
    push 20
    call general_handler
    add esp, 4
    iret

interupt_21:
    push 21
    call general_handler
    add esp, 4
    iret

interupt_22:
    push 22
    call general_handler
    add esp, 4
    iret

interupt_23:
    push 23
    call general_handler
    add esp, 4
    iret

interupt_24:
    push 24
    call general_handler
    add esp, 4
    iret

interupt_25:
    push 25
    call general_handler
    add esp, 4
    iret

interupt_26:
    push 26
    call general_handler
    add esp, 4
    iret

interupt_27:
    push 27
    call general_handler
    add esp, 4
    iret

interupt_28:
    push 28
    call general_handler
    add esp, 4
    iret

interupt_29:
    push 29
    call general_handler
    add esp, 4
    iret

interupt_30:
    push 30
    call general_handler
    add esp, 4
    iret

interupt_31:
    push 31
    call general_handler
    add esp, 4
    iret

interupt_32:
    push 32
    call general_handler
    add esp, 4
    iret

interupt_33:
    push 33
    call general_handler
    add esp, 4
    iret

global interupt_table
interupt_table:
    dd interupt_0
    dd interupt_1
    dd interupt_2
    dd interupt_3
    dd interupt_4
    dd interupt_5
    dd interupt_6
    dd interupt_7
    dd interupt_8
    dd interupt_9
    dd interupt_10
    dd interupt_11
    dd interupt_12
    dd interupt_13
    dd interupt_14
    dd interupt_15
    dd interupt_16
    dd interupt_17
    dd interupt_18
    dd interupt_19
    dd interupt_20
    dd interupt_21
    dd interupt_22
    dd interupt_23
    dd interupt_24
    dd interupt_25
    dd interupt_26
    dd interupt_27
    dd interupt_28
    dd interupt_29
    dd interupt_30
    dd interupt_31
    dd interupt_32
    dd interupt_33
