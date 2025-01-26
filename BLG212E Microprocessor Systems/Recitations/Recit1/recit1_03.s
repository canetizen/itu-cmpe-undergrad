        AREA example, CODE, READONLY    ; Declare new area
        ENTRY                           ; Declare as entry point
        ALIGN                           ; Ensures that __main addresses the following instruction

__main  FUNCTION                        ; Enable Debug
        EXPORT __main                   ; Make __main as global to access from startup file
        MOVS     R0, #48                ; Set up parameters (example values)
        MOVS     R1, #18
        BL       doGCD                   ; Call GCD subroutine

stop    B    stop                       ; Branch stop

doGCD   CMP     R0, R1                  ; Compare a and b (R0 and R1)
        BEQ     endGCD                  ; If they are equal, branch to endGCD
        BGT     subtractA               ; If a > b, branch to subtractA
        B       subtractB               ; Else, branch to subtractB

subtractA SUBS    R0, R0, R1              ; a = a - b
          B       doGCD                   ; Repeat the loop

subtractB SUBS    R1, R1, R0              ; b = b - a
          B       doGCD                   ; Repeat the loop

endGCD    MOV     R0, R0                   ; Move the result (GCD) into R0 for returning
          BX      LR                      ; Return from subroutine

        ENDFUNC                         ; Finish function
        END                             ; Finish assembly file
