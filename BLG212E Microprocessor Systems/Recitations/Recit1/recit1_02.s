        AREA example, CODE, READONLY    
        ENTRY                           
        ALIGN                           
__main  FUNCTION                        
        EXPORT __main                   
        MOVS     R0, #10                 ; Set up parameters
        MOVS     R1, #3
        BL      doadd                   ; Call subroutine

stop    B    stop                       ; Branch stop

doadd   ADD     R0, R0, R1              ; Subroutine code
        BX      LR                      ; Return from subroutine

        ENDFUNC                         ; Finish function
        END                             ; Finish assembly file