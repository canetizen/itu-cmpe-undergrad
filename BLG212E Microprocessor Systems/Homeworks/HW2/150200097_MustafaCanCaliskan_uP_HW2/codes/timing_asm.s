; BLG 212E Homework 2
; Mustafa Can Caliskan
; 150200097

	AREA    |.text|, CODE, READONLY
    ALIGN
    THUMB
    EXPORT  Systick_Start_asm
    EXPORT  Systick_Stop_asm
    EXPORT  SysTick_Handler
    EXTERN  ticks
    EXTERN  SystemCoreClock

; SysTick register addresses
SysTick_CTRL    EQU     0xE000E010
SysTick_LOAD    EQU     0xE000E014
SysTick_VAL     EQU     0xE000E018

; CTRL register bits
SysTick_CTRL_ENABLE      EQU     0x00000001
SysTick_CTRL_TICKINT     EQU     0x00000002
SysTick_CTRL_CLKSOURCE   EQU     0x00000004

SysTick_Handler
        PUSH    {LR}               ; Save the link register
        LDR     R0, =ticks         ; Load address of 'ticks' variable
        LDR     R1, [R0]           ; Load current value of ticks
        ADDS    R1, R1, #1         ; Increment ticks value by 1
        STR     R1, [R0]           ; Store updated ticks value
        POP     {PC}               ; Restore program counter and return

Systick_Start_asm
        PUSH    {R4, R5, LR}       ; Save registers R4, R5, and LR

        ; Reset ticks to 0
        LDR     R0, =ticks         ; Load address of 'ticks' variable
        MOVS    R1, #0             ; Move 0 into R1
        STR     R1, [R0]           ; Store 0 in ticks

        MOVS    R0, #249           ; Load 249 into R0 (for SysTick timer period)

        ; Set LOAD register value
        LDR     R1, =SysTick_LOAD  ; Load SysTick_LOAD register address
        STR     R0, [R1]           ; Store the value of R0 (249) in SysTick_LOAD

        ; Reset VAL register
        LDR     R1, =SysTick_VAL   ; Load SysTick_VAL register address
        MOVS    R0, #0             ; Move 0 into R0
        STR     R0, [R1]           ; Store 0 in SysTick_VAL

        ; Set CTRL register to enable SysTick
        LDR     R1, =SysTick_CTRL  ; Load SysTick_CTRL register address
        MOVS    R0, #7             ; Set all bits (Enable, Interrupt, Clock Source)
        STR     R0, [R1]           ; Store value of R0 in SysTick_CTRL

        POP     {R4, R5, PC}       ; Restore saved registers and return

Systick_Stop_asm
        PUSH    {R4, LR}           ; Save registers R4 and LR

        ; Stop SysTick by clearing all bits in CTRL register
        LDR     R1, =SysTick_CTRL  ; Load SysTick_CTRL register address
        MOVS    R0, #0             ; Set R0 to 0 (clear all bits)
        STR     R0, [R1]           ; Store 0 in SysTick_CTRL to stop SysTick

        ; Return the value of ticks
        LDR     R0, =ticks         ; Load address of 'ticks' variable
        LDR     R0, [R0]           ; Load the value of ticks into R0

        POP     {R4, PC}           ; Restore saved registers and return

        END
