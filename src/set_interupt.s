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
