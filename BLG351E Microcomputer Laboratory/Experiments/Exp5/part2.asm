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
flag		.byte	00000000b
array		.byte	00111111b, 00000110b, 01011011b, 01001111b, 01100110b, 01101101b, 01111101b, 00000111b, 011111111b, 01101111b
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
init_INT	bis.b 	#040h, &P2IE
			and.b	#0BFh, &P2SEL
			and.b	#0BFh, &P2SEL2

			bis.b	#040h, &P2IES
			clr		&P2IFG
			eint

SetupP1		bis.b 	#0FFh,&P1DIR

			bis.b	#008h,&P2DIR
			bis.b	#008h,&P2OUT
			mov.w   #00h, R5

SetupP2		mov.w	R5, R13
			mov.w	#array, R12

Mainloop    mov.w   #array, R12             ; Reset R12 to array base address
            add.w   R13, R12                ; Calculate array offset
            mov.b   0(R12), &P1OUT          ; Send value to P1OUT (7-segment)
            call    #Delay                  ; 1-second delay
            add.w   #2, R13                     ; Increment counter
            cmp.w   #0x0A, R13              ; Check if counter == 10
            jl      Mainloop              ; If not, loop back
            mov.w   #0, R13                 ; Reset counter to 0
            jmp     SetupP2                ; Restart loop


Delay		mov.w	#0Ah, R14
L2			mov.w	#07A00h, R15
L1			dec.w	R15
			jnz		L1
			dec.w	R14
			jnz		L2
			ret

ISR			dint
			xor.w	#01h, R5
			dec.w	R13
			clr		&P2IFG
			eint
			reti

exit		nop
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
            .sect	".int03"
            .short	ISR