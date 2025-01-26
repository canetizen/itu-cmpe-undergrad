;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for BBS Random Number Generator
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point
;-------------------------------------------------------------------------------
            .data

; Seven-segment display patterns
arr         .byte 00111111b , 00000110b , 01011011b , 01001111b , 01100110b, 01101101b , 01111101b , 00000111b , 01111111b , 01101111b
lastelement

; BBS parameters
seed        .word   5       ; Starting seed value
p           .word   11      ; First prime number
q           .word   13      ; Second prime number
m           .word   143     ; M = p * q (modulus)
current     .word   0       ; Currently generated random value

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory
            .retain
            .retainrefs

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Set up the stack pointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Disable the watchdog timer

;-------------------------------------------------------------------------------
; Interrupt Setup
;-------------------------------------------------------------------------------
setup_INT
            ; Configure P2.6 for Reset, P2.5 for Stop, P2.4 for Start
            bis.b #0F0h, &P2IE              ; Enable interrupts on P2.4, P2.5, P2.6
            and.b #08Fh, &P2SEL             ; Set pins as GPIO
            and.b #08Fh, &P2SEL2
            bis.b #070h, &P2IES             ; Trigger interrupts on falling edge
            clr   &P2IFG                    ; Clear any interrupt flags
            eint                            ; Enable global interrupt handling

;-------------------------------------------------------------------------------
; Main Setup
;-------------------------------------------------------------------------------
InitSetup
            bis.b #0FFh, &P1DIR            ; Configure P1 as output
            bis.b #00Fh, &P2DIR            ; Set lower nibble of P2 as output
            bic.b #0FFh, &P1OUT            ; Clear all outputs on P1
            mov.b #001h, &P2OUT            ; Initialize display settings

            ; Initialize the BBS random generator
            mov.w &seed, r15               ; Load the starting seed value
            call #BBS_Generate             ; Generate the first random number

;-------------------------------------------------------------------------------
; Main Loop
;-------------------------------------------------------------------------------
MainLoop        jmp DisplayLoop              ; Continuously display the current value

DisplayLoop
            call #BCD_Convert
            mov.b @r4, &P1OUT             ; Show the units digit on the display
            mov.b #08h, &P2OUT
            nop
            nop
            clr &P1OUT
            clr &P2OUT
            mov.b @r5, &P1OUT             ; Show the tens digit on the display
            mov.b #04h, &P2OUT
            nop
            nop
            clr &P1OUT
            clr &P2OUT
            mov.b @r6, &P1OUT             ; Show the hundreds digit on the display
            mov.b #02h, &P2OUT
            nop
            nop
            clr &P1OUT
            clr &P2OUT
            mov.b @r7, &P1OUT             ; Show the thousands digit on the display
            mov.b #01h, &P2OUT
            nop
            nop
            clr &P1OUT
            clr &P2OUT
            jmp MainLoop

;-------------------------------------------------------------------------------
; Interrupt Service Routines
;-------------------------------------------------------------------------------
P2_InterruptHandler      ; Handle Port 2 interrupts
            push r15
            mov.b &P2IFG, r15            ; Check which interrupt triggered

            bit.b #020h, r15             ; Test if Stop button (P2.5) was pressed
            jnz GenerateNextNumber            ; If true, generate a new random number
            jmp ISRExit

GenerateNextNumber
            mov.w &current, r15          ; Use the current value as the new seed
            call #BBS_Generate               ; Generate the next random number

ISRExit
            clr &P2IFG                   ; Clear all interrupt flags
            pop r15
            reti

;-------------------------------------------------------------------------------
; ModuloNumbers: Compute r15 = r15 mod r14
;-------------------------------------------------------------------------------
ModuloNumbers
            push r13
ModCycle
            cmp r14, r15                 ; Compare r15 with r14
            jl ModEnd                   ; If r15 < r14, the remainder is found
            sub r14, r15                 ; Subtract r14 from r15
            jmp ModCycle                ; Repeat until r15 < r14

ModEnd
            pop r13
            ret

;-------------------------------------------------------------------------------
; MultiplyNumbers: Compute r15 = r14 * r13
;-------------------------------------------------------------------------------
MultiplyNumbers
            push r12
            clr r12                       ; Initialize result to 0

MultCycle
            bit #1, r13                   ; Check the least significant bit of r13
            jz MultSkip                   ; If bit is 0, skip addition
            add r14, r12                  ; Add r14 to the result

MultSkip
            rla r14                       ; Shift r14 left by 1 bit
            rra r13                       ; Shift r13 right by 1 bit
            jnz MultCycle                 ; Continue if r13 is not zero

            mov.w r12, r15               ; Store the result in r15
            pop r12
            ret

;-------------------------------------------------------------------------------
; DivideNumbers: Compute r15 = r15/r14
;-------------------------------------------------------------------------------
DivideNumbers      push r13
            clr r13                     ; Initialize quotient to 0

DivCycle    cmp r14, r15               ; Check if divisor is less than dividend
            jl DivEnd                 ; If true, division is complete
            sub r14, r15               ; Subtract divisor from dividend
            inc r13                    ; Increment quotient
            jmp DivCycle               ; Repeat the process

DivEnd    mov.w r13, r15            ; Store the result in r15
            pop r13
            ret

;-------------------------------------------------------------------------------
; BCD_ConverT: Convert current random number to BCD for display
;-------------------------------------------------------------------------------
BCD_Convert     push r14
            push r13

            mov.w &current, r13          ; Load the current random value

            ; Extract the units digit (r13 mod 10)
            mov.w #10, r14              ; Set divisor to 10
            mov.w r13, r15              ; Copy the number to r15
            call #ModuloNumbers                ; Compute the remainder (units digit)
            mov.w #arr, r4              ; Point to the seven-segment pattern array
            add.w r15, r4               ; Get the corresponding segment pattern

            ; Extract the tens digit ((r13/10) mod 10)
            mov.w r13, r15              ; Restore the original number
            mov.w #10, r14              ; Set divisor to 10
            call #DivideNumbers                ; Compute r13/10
            mov.w #10, r14              ; Set divisor to 10
            call #ModuloNumbers                ; Compute the remainder (tens digit)
            mov.w #arr, r5              ; Point to the pattern array
            add.w r15, r5               ; Get the corresponding segment pattern

            ; Extract the hundreds digit ((r13/100) mod 10)
            mov.w r13, r15              ; Restore the original number
            mov.w #100, r14             ; Set divisor to 100
            call #DivideNumbers                ; Compute r13/100
            mov.w #10, r14              ; Set divisor to 10
            call #ModuloNumbers                ; Compute the remainder (hundreds digit)
            mov.w #arr, r6              ; Point to the pattern array
            add.w r15, r6               ; Get the corresponding segment pattern

            ; Extract the thousands digit (r13/1000)
            mov.w r13, r15              ; Restore the original number
            mov.w #1000, r14            ; Set divisor to 1000
            call #DivideNumbers                ; Compute r13/1000
            mov.w #arr, r7              ; Point to the pattern array
            add.w r15, r7               ; Get the corresponding segment pattern

            pop r13
            pop r14
            ret

;-------------------------------------------------------------------------------
; BBS Random Number Generator
;-------------------------------------------------------------------------------
BBS_Generate
            push r14
            push r13

            ; Compute r = (s^2) mod M
            mov.w r15, r14                ; r14 = seed value
            mov.w r15, r13                ; r13 = seed value
            call #MultiplyNumbers                ; Calculate s^2

            mov.w &m, r14                 ; Load modulus M
            call #ModuloNumbers                  ; Compute (s^2) mod M

            mov.w r15, &current           ; Update the current random value

            pop r13
            pop r14
            ret

; Rest of the code remains the same
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack

            .sect   ".reset"              ; MSP430 RESET Vector
            .short  RESET

            .sect   ".int03"              ; Port 2 interrupt
            .short  P2_InterruptHandler