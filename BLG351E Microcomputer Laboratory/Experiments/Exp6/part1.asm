; MSP430 Assembly Code for 7-Segment Display

            .cdecls C,LIST,"msp430.h"       ; Include device header file

;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------

.data
array       .byte   00111111b , 00000110b , 01011011b , 01001111b , 01100110b, 01101101b , 01111101b , 00000111b , 01111111b , 01101111b
lastElement
;-------------------------------------------------------------------------------
.text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
Display_Init
            bis.b #0FFh, &P1DIR             ; Configure P1 as output
		    bis.b #00Fh, &P2DIR              ; Configure P2 lower nibble as output
		    bic.b #0FFh, &P1OUT              ; Clear P1 outputs

            mov.w #array, r4


MainLoop
            mov.b   3(R4), &P1OUT
            mov.b   #08h , &P2OUT
            call    #DELAY
            clr     & P1OUT
		    clr     & P2OUT

            mov.b   2(R4), &P1OUT
            mov.b   #04h , &P2OUT
            call    #DELAY
            clr     & P1OUT
		    clr     & P2OUT

            mov.b   1(R4), &P1OUT
            mov.b   #02h , &P2OUT
            CALL    #DELAY
            clr     & P1OUT
		    clr     & P2OUT

            mov.b   0(R4), &P1OUT
            mov.b   #01h , &P2OUT
            call    #DELAY
            clr     & P1OUT
		    clr     & P2OUT

            jmp     MainLoop

DELAY       mov.w   #0x000F, R14

L1          dec.w   R14
            jnz     L1
            ret

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
