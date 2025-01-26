        AREA example, CODE, READONLY    ; Declare new area
        ENTRY                           ; Declare as entry point
        ALIGN                           ; Ensures that __main addresses the following instruction
		
		EXPORT __main
__main  FUNCTION                        ; Enable Debug
		BL SysTick_Init
		LDR R0, =10000
        BL delay                        ; Call the delay subroutine
        
stop    B    stop                       ; Branch to stop to end execution
		ENDFUNC


SysTick_Init	FUNCTION																
		PUSH {R0-R2, LR}					; Save the modified regiters.
		BL	 SysTick_Stop					; Stop the System Tick Timer initially.
		; CPU 16 MHz, Frequency 1000 Hz
		; Period = (ReloadValue +1)/CPUFreq
		; ReloadValue + 1 = CPUFreq/Freq
		; ReloadValue + 1 = 16.000.000 / 1000
		; ReloadValue = 15.999
		LDR	 R0, =0xE000E014				; Load SYST_RVR Address.
		LDR  R1, =47999						; R1 = 15999 //Reload Value.	
		STR  R1, [R0]						; Set the Reload Value Register.
		LDR	 R0, =0xE000E018				; Load SYST_CVR Address.
		MOVS R1, #0							; R1 = 0
		STR  R1, [R0]						; Clear the Current Value Register.
		LDR	 R0, =0xE000E010				; Load SYST_CSR Address.
		LDR  R1, [R0]						; Load Control and Status Register to R1.
	    MOVS R2, #7							; MOV #7 to R2.
		ORRS R1, R1, R2						; Set CLKSOURCE, TICKINT, and ENABLE flags.	
		STR  R1, [R0]						; Set the Reload Value Register to enable interrupt and timer.
		POP  {R0-R2, PC}					; Restore saved registers and return with PC.	
		ENDFUNC

;*******************************************************************************				

;@brief 	This function will be used to stop the System Tick Timer
SysTick_Stop	FUNCTION				
		PUSH {R0-R2}						; Save the modified regiters.
		LDR	 R0, =0xE000E010				; Load SYST_CSR Address.
		LDR  R1, [R0]						; Load Control and Status Register to R1.
		LDR  R2, =0xFFFFFFFC				; MOVS Mask value to R2.
		ANDS R1, R1, R2						; Clear TICKINT and ENABLE flags.
		STR  R1, [R0]						; Store the new register value.
											; to disable timer and interrupt.
		POP  {R0-R2}						; Restore saved registers.
		BX LR								; Return.				
		ENDFUNC

        EXPORT SysTick_Handler
SysTick_Handler FUNCTION
        SUBS R5, R5, #1                ; Decrement TimeDelay
        BX LR                          ; Return from handler
        ENDFUNC                        ; Finish function

delay   FUNCTION
        MOVS R5, R0                   ; Store input delay value in TimeDelay

loop    CMP R5, #0                    ; Load current TimeDelay value
        BNE loop                       ; If not zero, branch to loop
        BX LR                          ; Return when TimeDelay is zero
        ENDFUNC                        ; Finish function