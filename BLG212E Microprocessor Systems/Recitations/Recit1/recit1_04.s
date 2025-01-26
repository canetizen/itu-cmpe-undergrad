        AREA example, CODE, READONLY    ; Declare new area
        ENTRY                           ; Declare as entry point
        ALIGN                           ; Ensures that __main addresses the following instruction

__main  FUNCTION                        ; Enable Debug
        EXPORT __main                   ; Make __main as global to access from startup file
		LDR R0, =var1                    ; Load the address of 'myVar' into r0
		LDR R1, [R0]                    ; Load the value at the address in r0 into r1 (0x12345678)
		LDR R2, var1

stop    B    stop                       ; Branch stop
        
var1    DCD 0x12345678                  ; Define a 32-bit constant in memory
	
		ENDFUNC                         ; Finish function
        END                             ; Finish assembly file