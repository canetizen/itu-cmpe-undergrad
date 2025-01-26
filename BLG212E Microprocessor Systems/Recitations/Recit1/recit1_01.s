        AREA example, CODE, READONLY    ;Declare new area
        ENTRY                             ;Declare as antry point
        ALIGN                            ;Ensures that __main addresses the following instruction
__main  FUNCTION                        ;Enable Debug
        EXPORT __main                    ;Make __main as global to access from startup file
        MOVS     R0, #10        ; Set up parameters
        MOVS     R1, #3
        ADD      R0, R0, R1     ; r0 = r0 + r1

stop    B    stop                        ;Branch stop

        ENDFUNC                            ;Finish function
        END                                ;Finish assembly file