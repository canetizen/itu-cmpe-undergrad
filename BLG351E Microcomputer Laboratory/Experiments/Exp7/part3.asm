;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for Random Number Distribution Analysis
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point
;-------------------------------------------------------------------------------
            .data

; Seven-segment display patterns
arr         .byte 00111111b , 00000110b , 01011011b , 01001111b , 01100110b, 01101101b , 01111101b , 00000111b , 01111111b , 01101111b
lastelement

; Parameters for BBS random number generator
seed        .word   5       ; Initial seed value
p           .word   11      ; First prime number
q           .word   13      ; Second prime number
m           .word   143     ; M = p * q (product of primes)
current     .word   0       ; Stores the current random number

; Variables for distribution analysis
numbers     .space  256     ; Memory space for 128 random numbers (2 bytes per number)
counters    .space  16      ; Memory space for counting occurrences of values (0-7)
num_count   .word   0       ; Tracks how many numbers have been generated
max_nums    .word   128     ; Total number of random numbers to generate
display_mode .word  0       ; 0 = current number display, 1 = distribution counts display

;-------------------------------------------------------------------------------
            .text                           ; Instructions in program memory
;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stack pointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Disable the watchdog timer

;-------------------------------------------------------------------------------
; Interrupt Service Routine for P2.5 button
;-------------------------------------------------------------------------------
P2_ISR      push r15
            push r14
            mov.b &P2IFG, r15            ; Retrieve the interrupt flag

            bit.b #020h, r15             ; Check if P2.5 triggered the interrupt
            jnz check_mode               ; If true, check the mode
            jmp P2_ISR_End

check_mode  mov.w &num_count, r14
            cmp.w &max_nums, r14         ; Check if all numbers are generated
            jge show_distribution        ; If yes, switch to distribution display
            call #store_random_value     ; Otherwise, generate and store next number
            jmp P2_ISR_End

show_distribution                        ; Switch to distribution display mode
            mov.w #1, &display_mode
            call #analyze_distribution   ; Perform frequency analysis
            jmp P2_ISR_End

P2_ISR_End  clr &P2IFG                  ; Clear interrupt flags
            pop r14
            pop r15
            reti

;-------------------------------------------------------------------------------
; Generate and Store Random Number
;-------------------------------------------------------------------------------
store_random_value
            mov.w &current, r15          ; Use current random number as seed
            call #BBS_next               ; Generate the next random number
            
            ; Limit the number to range 0-7
            mov.w &current, r15
            mov.w #8, r14                ; Perform modulo 8 operation
            call #calculate_modulus
            mov.w r15, &current          ; Save the adjusted random number
            
            ; Save the random number to memory
            mov.w &num_count, r14
            rla.w r14                    ; Convert index to word address
            mov.w #numbers, r13
            add.w r14, r13               ; Compute memory address
            mov.w &current, 0(r13)       ; Store the random number
            
            inc.w &num_count             ; Increment the count of generated numbers
            ret

;-------------------------------------------------------------------------------
; Analyze the Distribution of Random Numbers
;-------------------------------------------------------------------------------
analyze_distribution
            push r13
            push r14
            push r15
            
            ; Reset all counters to zero
            mov.w #counters, r13
            mov.w #8, r14                ; 8 possible values (0-7)
clear_loop  clr.w 0(r13)
            inc.w r13
            dec.w r14
            jnz clear_loop
            
            ; Count the occurrences of each number
            mov.w #numbers, r13
            mov.w #0, r14                ; Initialize index to 0
count_loop  cmp.w &max_nums, r14         ; Check if all numbers are processed
            jeq count_done
            
            mov.w @r13, r15              ; Fetch a number from memory
            rla.w r15                    ; Compute index for word addressing
            mov.w #counters, r13
            add.w r15, r13               ; Address the corresponding counter
            inc.w 0(r13)                 ; Increment the counter
            
            inc.w r14                    ; Move to the next number
            inc.w r13                    ; Increment memory pointer
            jmp count_loop
            
count_done  pop r15
            pop r14
            pop r13
            ret

;-------------------------------------------------------------------------------
; Convert Number for Display
;-------------------------------------------------------------------------------
convert_to_BCD
            push r14
            push r13

            mov.w &display_mode, r13
            tst.w r13
            jnz show_counts              ; If mode = 1, show distribution counts

            ; Display the current random number
            mov.w &current, r13
            jmp convert_display

show_counts
            mov.w #counters, r14         ; Address the counters
            mov.w 0(r14), r13            ; Fetch the current counter value
            
convert_display
            ; Perform BCD conversion for 7-segment display
            ; (Include modular conversion and memory addressing)

            pop r13
            pop r14
            ret

;-------------------------------------------------------------------------------
; Perform Multiplication
;-------------------------------------------------------------------------------
perform_multiplication
            push r12
            clr r12                       ; Clear the result register

mult_loop
            bit #1, r13                   ; Check if the LSB of r13 is 1
            jz mult_skip                  ; Skip addition if not set
            add r14, r12                  ; Add r14 to the result

mult_skip
            rla r14                       ; Shift r14 left
            rra r13                       ; Shift r13 right
            jnz mult_loop                 ; Continue until r13 is zero

            mov.w r12, r15               ; Store the result
            pop r12
            ret

;-------------------------------------------------------------------------------
; Calculate Modulus
;-------------------------------------------------------------------------------
calculate_modulus
            push r13
mod_loop
            cmp r14, r15                 ; Compare divisor and dividend
            jl mod_done                  ; Exit if dividend < divisor
            sub r14, r15                 ; Subtract divisor
            jmp mod_loop                 ; Repeat until complete

mod_done
            pop r13
            ret

;-------------------------------------------------------------------------------
; Perform Division
;-------------------------------------------------------------------------------
perform_division
            push r13
            clr r13                     ; Reset quotient

div_loop    cmp r14, r15               ; Compare divisor and dividend
            jl div_done                 ; Exit if dividend < divisor
            sub r14, r15               ; Subtract divisor
            inc r13                    ; Increment quotient
            jmp div_loop               ; Continue until division is complete

div_done    mov.w r13, r15            ; Store the quotient
            pop r13
            ret

;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack

            .sect   ".reset"              ; MSP430 RESET Vector
            .short  RESET

            .sect   ".int03"              ; Port 2 interrupt
            .short  P2_ISR