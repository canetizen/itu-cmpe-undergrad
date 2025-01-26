;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
		.data
array		.byte	0111111b, 0000110b, 1011011b, 1001111b, 1100110b, 1101101b, 1111101b, 0000111b, 11111111b, 1101111b
lastElement
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------

RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------

SetupP1     bis.b   #0xFF,&P1DIR            ; Set Port 1 as output
            bis.b   #0x08,&P2DIR            ; Set P2.3 as output
            bis.b   #0x08,&P2OUT            ; Turn on P2.3
            mov.w   #0, R13                 ; Initialize R13 to 0 (counter/index)

Mainloop    mov.w   #array, R12             ; Reset R12 to array base address
            add.w   R13, R12                ; Calculate array offset
            mov.b   0(R12), &P1OUT          ; Send value to P1OUT (7-segment)
            call    #Delay                  ; 1-second delay
            inc.w   R13                     ; Increment counter
            cmp.w   #0x0A, R13              ; Check if counter == 10
            jne     Mainloop                ; If not, loop back
            mov.w   #0, R13                 ; Reset counter to 0
            jmp     Mainloop                ; Restart loop

; Delay Function (1 Second)
Delay       mov.w   #0x0A, R14              ; Outer loop count (10)
L2          mov.w   #0x7A00, R15           ; Inner loop count (31250)
L1          dec.w   R15                    ; Decrement inner loop
            jnz     L1                      ; If not zero, loop
            dec.w   R14                    ; Decrement outer loop
            jnz     L2                      ; If not zero, loop
            ret                            ; Return from delay

exit        nop                            ; Program exit point

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
