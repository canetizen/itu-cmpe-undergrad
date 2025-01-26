;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for MSWS Random Number Generator
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Declare program entry point
;-------------------------------------------------------------------------------
            .data

; Seven-segment display encoding patterns
arr         .byte 00111111b , 00000110b , 01011011b , 01001111b , 01100110b, 01101101b , 01111101b , 00000111b , 01111111b , 01101111b
lastelement

; MSWS parameters
seed        .word   5   ; Initial value used for random generation
x_value     .word   0   ; Holds the x value in MSWS calculation
w_value     .word   0   ; Holds the w value in MSWS calculation
current     .word   0   ; Stores the generated random number in range 0-128

;-------------------------------------------------------------------------------
            .text                           ; Begin program memory assembly
            .retain
            .retainrefs

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Set up the stack pointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Disable the watchdog timer to stop resets

;-------------------------------------------------------------------------------
; Interrupt Configuration
;-------------------------------------------------------------------------------
setup_INT
            ; Configure P2.6 as Reset, P2.5 as Stop, P2.4 as Start
            bis.b #0F0h, &P2IE              ; Enable interrupts on P2.4, P2.5, P2.6
            and.b #08Fh, &P2SEL             ; Set the pins to GPIO mode
            and.b #08Fh, &P2SEL2
            bis.b #070h, &P2IES             ; Trigger interrupts on falling edges
            clr   &P2IFG                    ; Clear any pending interrupt flags
            eint                            ; Enable global interrupts

;-------------------------------------------------------------------------------
; Initial Setup
;-------------------------------------------------------------------------------
Setup
            bis.b #0FFh, &P1DIR            ; Configure all P1 pins as outputs
            bis.b #00Fh, &P2DIR            ; Set lower nibble of P2 as output
            bic.b #0FFh, &P1OUT            ; Ensure P1 outputs are cleared
            mov.b #001h, &P2OUT            ; Initialize the display with a default value

            ; Initialize MSWS generator
            mov.w &seed, r15               ; Load the initial seed value
            call #GenerateRandomNumber     ; Generate the first random number

;-------------------------------------------------------------------------------
; Main Program Loop
;-------------------------------------------------------------------------------
Main        jmp HandleDisplay             ; Continuously display the generated value

HandleDisplay

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
            jmp Main

;-------------------------------------------------------------------------------
; MSWS Random Number Generator
;-------------------------------------------------------------------------------
GenerateRandomNumber

            push r14
            push r13

            ; Step 1: Calculate square of x (x = x^2)
            mov.w &x_value, r14          ; Load x value into r14
            mov.w r14, r13               ; Copy x to r13 for multiplication
            call #CalculateSquare        ; Compute x^2, result in r15
            mov.w r15, &x_value          ; Save squared value back to x

            ; Step 2: Update w (w = w + seed) and add w to x
            mov.w &w_value, r14          ; Load current w value
            add.w &seed, r14             ; Increment w by the seed value
            mov.w r14, &w_value          ; Save the updated w value
            add.w r14, r15               ; Add w to x
            mov.w r15, &x_value          ; Save updated x value

            ; Step 3: Perform rotation (x >> 4) | (x << 4)
            mov.w r15, r14               ; Copy x to r14
            rra.w r15                    ; Perform 4 right rotations
            rra.w r15
            rra.w r15
            rra.w r15
            mov.w r14, r13               ; Copy original x to r13
            rla.w r13                    ; Perform 4 left rotations
            rla.w r13
            rla.w r13
            rla.w r13
            bis.w r13, r15               ; Combine rotated values with bitwise OR

            ; Step 4: Limit the result to range 0-128 using ComputeModulo operation
            mov.w #129, r14              ; Set modulus value to 129
            call #ComputeModulo          ; Compute remainder after division by 129

            mov.w r15, &current          ; Save the final random value

            pop r13
            pop r14
            call #ConvertToBCD
            ret


;-------------------------------------------------------------------------------
; CalculateSquare: Compute r15 = r14 * r13
;-------------------------------------------------------------------------------
CalculateSquare
            push r12
            clr r12                       ; Clear the result accumulator

MultiplyNumbersLoop
            bit #1, r13                   ; Check if the least significant bit of r13 is 1
            jz SkipAddition               ; Skip addition if the bit is 0
            add r14, r12                  ; Add r14 to the result

SkipAddition
            rla r14                       ; Shift r14 left by 1
            rra r13                       ; Shift r13 right by 1
            jnz MultiplyNumbersLoop       ; Continue loop if r13 is not zero

            mov.w r12, r15               ; Store the final result in r15
            pop r12
            ret

;-------------------------------------------------------------------------------
; ComputeModulo: Compute r15 = r15 mod r14
;-------------------------------------------------------------------------------
ComputeModulo
            push r13
ModuloCalculationLoop
            cmp r14, r15                 ; Compare dividend r15 with divisor r14
            jl ModuloDone                ; Exit loop if dividend is smaller than divisor
            sub r14, r15                 ; Subtract divisor from dividend
            jmp ModuloCalculationLoop    ; Repeat until r15 < r14

ModuloDone
            pop r13
            ret

;-------------------------------------------------------------------------------
; Interrupt Service Routines
;-------------------------------------------------------------------------------
Port2InterruptHandler   ; Handle interrupts triggered on Port 2
            push r15
            mov.b &P2IFG, r15            ; Retrieve interrupt flags

            bit.b #020h, r15             ; Check if Stop button (P2.5) was pressed
            jnz GenerateNextRandomValue  ; If pressed, compute the next random number
            jmp InterruptServiceEnd

GenerateNextRandomValue
            call #GenerateRandomNumber   ; Generate the next random value

InterruptServiceEnd
            clr &P2IFG                   ; Clear interrupt flags
            pop r15
            reti

;-------------------------------------------------------------------------------
; ConvertToBCD: Prepare current value for display on 7-segment
;-------------------------------------------------------------------------------
ConvertToBCD
            push r14
            push r13

            mov.w &current, r13          ; Load the current random number

            ; Extract the units digit (r13 mod 10)
            mov.w #10, r14              ; Set divisor to 10
            mov.w r13, r15              ; Copy value to r15
            call #ComputeModulo         ; Compute the remainder (units digit)
            mov.w #arr, r4              ; Load base address of segment patterns
            add.w r15, r4               ; Get the corresponding pattern

            ; Extract the tens digit ((r13/10) mod 10)
            mov.w r13, r15              ; Restore original value
            mov.w #10, r14              ; Set divisor to 10
            call #PerformDivision       ; Compute r13 divided by 10
            mov.w #10, r14              ; Set divisor to 10
            call #ComputeModulo         ; Compute the remainder (tens digit)
            mov.w #arr, r5              ; Load base address of segment patterns
            add.w r15, r5               ; Get the corresponding pattern

            ; Extract the hundreds digit ((r13/100) mod 10)
            mov.w r13, r15              ; Restore original value
            mov.w #100, r14             ; Set divisor to 100
            call #PerformDivision       ; Compute r13 divided by 100
            mov.w #10, r14              ; Set divisor to 10
            call #ComputeModulo         ; Compute the remainder (hundreds digit)
            mov.w #arr, r6              ; Load base address of segment patterns
            add.w r15, r6               ; Get the corresponding pattern

            ; Extract the thousands digit (r13/1000)
            mov.w r13, r15              ; Restore original value
            mov.w #1000, r14            ; Set divisor to 1000
            call #PerformDivision       ; Compute r13 divided by 1000
            mov.w #arr, r7              ; Load base address of segment patterns
            add.w r15, r7               ; Get the corresponding pattern

            pop r13
            pop r14
            ret

;-------------------------------------------------------------------------------
; PerformDivision: Compute r15 = r15 / r14
;-------------------------------------------------------------------------------
PerformDivision
            push r13
            clr r13                     ; Clear the counter (quotient)

DivisionCalculationLoop
            cmp r14, r15               ; Check if divisor is greater than dividend
            jl DivisionDone             ; If true, division is complete
            sub r14, r15               ; Subtract divisor from dividend
            inc r13                    ; Increment quotient
            jmp DivisionCalculationLoop ; Repeat the process

DivisionDone
            mov.w r13, r15            ; Store quotient in r15
            pop r13
            ret

; Rest of the code remains unchanged
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack

            .sect   ".reset"              ; Reset vector for MSP430
            .short  RESET

            .sect   ".int03"              ; Port 2 interrupt vector
            .short  Port2InterruptHandler