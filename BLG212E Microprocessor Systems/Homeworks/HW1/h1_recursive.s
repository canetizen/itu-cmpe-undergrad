    AREA MyCode, CODE, READONLY

    EXPORT max
    EXPORT knapSack
    EXPORT main
    EXPORT weight
    EXPORT profit

    ALIGN 1
max PROC
    MOVS    r3, r0
    MOVS    r0, r1
    CMP     r1, r3
    BGE     L2
    MOVS    r0, r3
L2
    BX      lr
    ENDP

    ALIGN 1
knapSack PROC
    PUSH    {r3, r4, r5, r6, r7, lr}
    MOV     r7, r8
    MOV     lr, r9
    MOVS    r4, r1
    PUSH    {r7, lr}
    MOVS    r7, r0
    CMP     r1, #0
    BEQ     L11
    CMP     r0, #0
    BEQ     L11
    LDR     r3, =weight
    MOV     r8, r3
    B       L7
L12
    CMP     r4, #0
    BEQ     L11
L7
    MOV     r3, r8
    SUBS    r4, r4, #1
    LSLS    r6, r4, #2
    LDR     r5, [r3, r6]
    CMP     r5, r7
    BGT     L12
    MOVS    r1, r4
    MOVS    r0, r7
    BL      knapSack
    MOVS    r1, r4
    MOV     r9, r0
    SUBS    r0, r7, r5
    BL      knapSack
    ADD     r6, r6, r8
    LDR     r6, [r6, #12]
    ADDS    r0, r6, r0
    CMP     r0, r9
    BLT     L13
L4
    POP     {r6, r7}
    MOV     r9, r7
    MOV     r8, r6
    POP     {r3, r4, r5, r6, r7, pc}
L11
    MOVS    r0, #0
    B       L4
L13
    MOV     r0, r9
    B       L4
    ENDP

    ALIGN 1
main PROC
    PUSH    {r4, lr}
    MOVS    r1, #3
    MOVS    r0, #50
    BL      knapSack
    LDR        r1, =profit
    LDR        r2, =weight
L17
    B       L17
    ENDP

    AREA MyData, DATA, READWRITE
    ALIGN 2
weight
    DCD 10, 20, 30

    ALIGN 2
profit
    DCD 60, 100, 120

    END