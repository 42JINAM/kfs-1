section .text
extern general_handler

%macro interupt 1 
interupt_%+%1:
	push %1
	call general_handler
	add esp, 4
	iret
%endmacro

%macro interupt_err 1
interupt_err_%+%1:
	push %1
	call general_handler
	add esp, 4
	iret
%endmacro

interupt 0
interupt 1
interupt 2
interupt 3
interupt 4
interupt 5
interupt 6
interupt 7
interupt_err 8
interupt 9
interupt_err 10
interupt_err 11
interupt_err 12
interupt_err 13
interupt_err 14
interupt 15
interupt 16
interupt_err 17
interupt 18
interupt 19
interupt 20
interupt_err 21
interupt 22
interupt 23
interupt 24
interupt 25
interupt 26
interupt 27
interupt 28
interupt 29
interupt 30
interupt 31
interupt 32
interupt 33

interupt_34:
    push 34
    call general_handler
    add esp, 4
    iret

interupt_35:
    push 35
    call general_handler
    add esp, 4
    iret

interupt_36:
    push 36
    call general_handler
    add esp, 4
    iret

interupt_37:
    push 37
    call general_handler
    add esp, 4
    iret

interupt_38:
    push 38
    call general_handler
    add esp, 4
    iret

interupt_39:
    push 38
    call general_handler
    add esp, 4
    iret

interupt_40:
    push 40
    call general_handler
    add esp, 4
    iret

interupt_41:
    push 41
    call general_handler
    add esp, 4
    iret

interupt_42:
    push 42
    call general_handler
    add esp, 4
    iret

interupt_43:
    push 43
    call general_handler
    add esp, 4
    iret

interupt_44:
    push 44
    call general_handler
    add esp, 4
    iret

interupt_45:
    push 45
    call general_handler
    add esp, 4
    iret

interupt_46:
    push 46
    call general_handler
    add esp, 4
    iret

interupt_47:
    push 47
    call general_handler
    add esp, 4
    iret

interupt_48:
    push 48
    call general_handler
    add esp, 4
    iret

interupt_49:
    push 49
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
    dd interupt_err_8
    dd interupt_9
    dd interupt_err_10
    dd interupt_err_11
    dd interupt_err_12
    dd interupt_err_13
    dd interupt_err_14
    dd interupt_15
    dd interupt_16
    dd interupt_err_17
    dd interupt_18
    dd interupt_19
    dd interupt_20
    dd interupt_err_21
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
    dd interupt_34
    dd interupt_35
    dd interupt_36
    dd interupt_37
    dd interupt_38
    dd interupt_39
    dd interupt_40
    dd interupt_41
    dd interupt_42
    dd interupt_43
    dd interupt_44
    dd interupt_45
    dd interupt_46
    dd interupt_47
    dd interupt_48
    dd interupt_49
