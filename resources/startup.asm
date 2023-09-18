.syntax unified
.cpu cortex-m4

.section .start_section, "ax"
.global startup

startup:
    LDR R0, =__stack_top        ; set stack
    MOV SP, R0                  ; initialize stack pointer
    BL _crt_init                ; init C runtime library
    BL main                     ; call main
    BL _crt_deinit              ; deinit C runtime library
    B .                         ; never return

.LTORG
