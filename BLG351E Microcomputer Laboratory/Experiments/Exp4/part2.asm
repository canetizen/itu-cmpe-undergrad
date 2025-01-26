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
result	.bss	resultArray,5
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



Setup
    mov #array, r5
    mov #resultArray, r10

Mainloop

	mov #20, r6
	mov #5, r7
	push r7
	push r6
	call #Divide
	pop r6
	jmp finish

Add:
	pop r5
    pop r8
    pop r9
    add r8, r9
    push r9
    push r5
    ret

Subtract:
	pop r5
    pop r8
    pop r9
    sub r9, r8
    push r8
    push r5
    ret


Multiply:
	pop r5
	pop r6
    pop r7
    push r5
	mov #0, r9
    mov #0, r8
	cmp #0,r6
	jl  Mul_R6
	jmp Mul_R7

Mul_R6:
    xor #0FFFFh, r6
    inc r6
    xor #0FFFFh, r8
	cmp #0,r7
	jl  Mul_R7
	jmp Multiply_Checked
Mul_R7
	cmp #0,r7
	jge  Multiply_Checked
    xor #0FFFFh, r7
    inc r7
    xor #0FFFFh, r8
	jmp Multiply_Checked

Multiply_Checked
	push r8
	jmp Multiply_Loop

Multiply_Loop:
	push r9
	push r6
    call #Add
    pop r9
	dec r7
	cmp #0, r7
	jne Multiply_Loop
	pop r8
	pop r5

	cmp #0, r8
	jeq Multiply_Done
	xor #0FFFFh, r9
	inc r9
	jmp Multiply_Done

Multiply_Done:
	push r9
	push r5
    ret

Divide:
	pop r5
	pop r6
    pop r7
    push r5
    mov #1, r4
	mov #0, r9
    mov #0, r8
	jmp Div_R6

Div_R6:
	cmp #0,r6
	jge  Div_R7
    xor #0FFFFh, r6
    inc r6
    xor #0FFFFh, r8
	jmp Div_R7
Div_R7
	cmp #0,r7
	jge  Divide_Checked
    xor #0FFFFh, r7
    inc r7
    xor #0FFFFh, r8
	jmp Divide_Checked

Divide_Checked
	cmp r6, r7
	jge Divide_Done
	push r8
	mov  #0, r8
	mov  r6, r9
	jmp Divide_Loop


Divide_Loop:
	push r7
	push r9
	call #Subtract
	pop r9
	inc r4
	cmp r9, r7
	jl Divide_Loop
	pop r8
	pop r5
	cmp #0, r8
	jeq Divide_Done
	xor #0FFFFh, r8
	inc r8
	jmp Divide_Done

Divide_Done
	push r4
	push r5
	ret


; Integer array
array .byte 1, 0, 127, 55
lastElement

finish
    nop


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
            
