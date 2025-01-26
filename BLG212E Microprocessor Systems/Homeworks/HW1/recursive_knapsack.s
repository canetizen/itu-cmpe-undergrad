; BLG 212E Microprocessor Systems
; Homework 1
; Mustafa Can Caliskan, 150200097
; Recursive Knapsack Algorithm

	AREA RECURSIVECODE, CODE, READONLY    ; Define a code area named RECURSIVECODE, read-only

    EXPORT __main                  ; Export the __main function for external linkage

    ALIGN 4                        ; Align data to 4-byte boundary

weight
    DCD 10, 20, 30                 ; Define a constant array of weights for items
    ALIGN 4                        ; Align data to 4-byte boundary

profit
    DCD 60, 100, 120               ; Define a constant array of profits for items
    ALIGN 4                        ; Align data to 4-byte boundary

    AREA PARAMETERS, NOINIT, READWRITE ; Define a data area named PARAMETERS, no initialization, read-write
    ALIGN 4                        ; Align data to 4-byte boundary

    AREA RECURSIVECODE, CODE, READONLY    ; Define another code area, read-only
    ALIGN 4                        ; Align code to 4-byte boundary

    THUMB                          ; Switch to THUMB instruction set
max PROC                           ; Define max procedure
    ALIGN 2                        ; Align procedure to 2-byte boundary
    MOVS    r3, r0                 ; Move first argument (r0) to r3
    MOVS    r0, r1                 ; Move second argument (r1) to r0
    CMP     r1, r3                 ; Compare r1 with r3
    BGE     maxEnd                 ; If r1 >= r3, branch to maxEnd
    MOVS    r0, r3                 ; Otherwise, set r0 to r3 (maximum value)
maxEnd
    BX      lr                     ; Return from procedure
    ENDP                           ; End of max procedure

    ALIGN 2                        ; Align code to 2-byte boundary

knapSack PROC                      ; Define knapSack procedure
    PUSH    {r3, r4, r5, r6, r7, lr} ; Save registers on the stack
    MOV     r7, r8                 ; Backup r8 to r7
    MOV     lr, r9                 ; Backup r9 to lr
    MOVS    r4, r1                 ; Move number of items (r1) to r4
    PUSH    {r7, lr}               ; Save r7 and lr to stack
    MOVS    r7, r0                 ; Move current capacity (r0) to r7
    CMP     r1, #0                 ; Check if number of items is 0
    BEQ     knapSackBaseCase       ; If true, branch to base case
    CMP     r0, #0                 ; Check if capacity is 0
    BEQ     knapSackBaseCase       ; If true, branch to base case
    LDR     r3, =weight            ; Load address of weights into r3
    MOV     r8, r3                 ; Save weights address in r8
    B       knapSackLoop           ; Branch to knapSack loop

knapSackCheck
    CMP     r4, #0                 ; Check if there are items left
    BEQ     knapSackBaseCase       ; If no items, branch to base case

knapSackLoop
    MOV     r3, r8                 ; Reload weights base address
    SUBS    r4, r4, #1             ; Decrement item count
    LSLS    r6, r4, #2             ; Calculate offset for current item
    LDR     r5, [r3, r6]           ; Load weight of current item
    CMP     r5, r7                 ; Compare item weight with capacity
    BGT     knapSackCheck          ; If item weight > capacity, skip to check
    MOVS    r1, r4                 ; Load current item index into r1
    MOVS    r0, r7                 ; Load current capacity into r0
    BL      knapSack               ; Recursive call excluding the item
    MOVS    r1, r4                 ; Reload item index for inclusion case
    MOV     r9, r0                 ; Save result of exclusion in r9
    SUBS    r0, r7, r5             ; Reduce capacity by item's weight
    BL      knapSack               ; Recursive call including the item
    ADD     r6, r6, r8             ; Offset for profit calculation
    LDR     r6, [r6, #12]          ; Load profit of included item
    ADDS    r0, r6, r0             ; Add profit of included item
    CMP     r0, r9                 ; Compare including and excluding cases
    BLT     knapSackUpdateMax      ; If excluding is better, update max
returnMax
    POP     {r6, r7}               ; Restore r6 and r7
    MOV     r9, r7                 ; Restore r9
    MOV     r8, r6                 ; Restore r8
    POP     {r3, r4, r5, r6, r7, pc} ; Restore registers and return
knapSackBaseCase
    MOVS    r0, #0                 ; Return 0 for base case
    B       returnMax              ; Branch to returnMax
knapSackUpdateMax
    MOV     r0, r9                 ; Update max to exclusion case
    B       returnMax              ; Branch to returnMax
    ENDP                           ; End of knapSack procedure

    ALIGN 2                        ; Align code to 2-byte boundary

__main PROC                        ; Define __main procedure
	ENTRY
    PUSH    {r4, lr}               ; Save r4 and link register
    MOVS    r1, #3                 ; Set number of items to 3
    MOVS    r0, #50                ; Set knapsack capacity to 50
    BL      knapSack               ; Call knapSack function
    LDR     r1, =profit            ; Load address of profits
    LDR     r2, =weight            ; Load address of weights
infiniteLoop
    B       infiniteLoop               ; Infinite loop (halt program)
    ENDP                           ; End of __main procedure

    END                            ; End of program
