; BLG 212E Microprocessor Systems
; Homework 1
; Mustafa Can Caliskan, 150200097
; Iterative Knapsack Algorithm

	AREA ITERATIVECODE, CODE, READONLY  ; Code section, read-only
    EXPORT __main                ; Export __main function (entry point)
        
    ALIGN 2                      ; Align memory to 2-byte boundary

profit  
    DCD 60 
    DCD 100
    DCD 120                      ; Profit array (value of each item)
        
    ALIGN 2
weight  
    DCD 10
    DCD 20
    DCD 30                       ; Weight array (weight of each item)

    AREA PARAMETERS, NOINIT, READWRITE ; PARAMETERS section, uninitialized, read/write allowed

dp
    SPACE 200                    ; DP array (used for knapsack dynamic programming solution)

    AREA ITERATIVECODE, CODE, READONLY  ; Code section, read-only
    
    ALIGN 1                      ; Align memory to 1-byte boundary
    THUMB                        ; Use THUMB instruction set
__main FUNCTION
    ENTRY                        ; Mark the entry point of the function
    PUSH    {r7, lr}             ; Save the current frame pointer and link register
    SUB     sp, sp, #16          ; Allocate 16 bytes of stack space
    ADD     r7, sp, #0           ; Set frame pointer to stack pointer

    MOVS    r1, #3               ; Total number of items
    MOVS    r0, #50              ; Knapsack capacity
    BL      knapSack             ; Call knapSack function
    MOVS    r0, r0               ; Dummy operation to ensure PARAMETERS dependency
    STR     r3, [r7, #12]        ; Store result in stack memory
    LDR     r1, =profit          ; Load address of profit array
    STR     r3, [r7, #8]         ; Store profit array address in stack
    LDR     r2, =weight          ; Load address of weight array
    STR     r3, [r7, #4]         ; Store weight array address in stack
    LDR     r3, =dp              ; Load address of dp array
    STR     r3, [r7]             ; Store dp array address in stack

infiniteLoop
    B       infiniteLoop         ; Infinite loop to terminate program

max
    PUSH    {r7, lr}             ; Save frame pointer and link register
    SUB     sp, sp, #8           ; Allocate 8 bytes of stack space
    ADD     r7, sp, #0           ; Set frame pointer to stack pointer

    STR     r0, [r7, #4]         ; Store first argument (value1)
    STR     r1, [r7]             ; Store second argument (value2)

    LDR     r2, [r7, #4]         ; Load value1 into r2
    LDR     r3, [r7]             ; Load value2 into r3

    CMP     r2, r3               ; Compare value1 and value2
    BGE     returnFirstValue     ; If value1 >= value2, branch to returnFirstValue

    MOVS    r2, r3               ; r2 = value2 (max value)

returnFirstValue
    MOVS    r0, r2               ; r0 = max(value1, value2)
    MOV     sp, r7               ; Restore stack pointer
    ADD     sp, sp, #8           ; Deallocate stack space
    POP     {r7, pc}             ; Restore frame pointer and return

knapSack
    PUSH    {r7, lr}             ; Save frame pointer and link register
    SUB     sp, sp, #16          ; Allocate 16 bytes of stack space
    ADD     r7, sp, #0           ; Set frame pointer to stack pointer

    STR     r0, [r7, #4]         ; Store knapsack capacity
    STR     r1, [r7]             ; Store number of items
    MOVS    r3, #1               ; Set current item index to 1
    STR     r3, [r7, #12]        ; Store current item index

knapSackOuterLoop
    LDR     r3, [r7, #4]         ; Load current capacity
    STR     r3, [r7, #8]         ; Store remaining capacity

knapSackInnerLoopStart
    LDR     r3, [r7, #12]        ; Load current item index
    SUBS    r2, r3, #1           ; Calculate 0-based index

    LDR     r3, =weight          ; Load weight array address
    LSLS    r2, r2, #2           ; Multiply index by 4 (word size)
    LDR     r3, [r3, r2]         ; Load weight of the current item

    LDR     r2, [r7, #8]         ; Load remaining capacity
    CMP     r2, r3               ; Compare remaining capacity with item weight
    BLT     skipCurrentItem      ; If item weight is greater, skip the item

    ; DP calculation
    LDR     r3, =dp              ; Load dp array address
    LDR     r2, [r7, #8]         ; Load remaining capacity
    LSLS    r2, r2, #2           ; Multiply capacity by 4 (word size)
    LDR     r0, [r3, r2]         ; Load dp[capacity]

    LDR     r3, [r7, #12]        ; Load current item index
    SUBS    r2, r3, #1           ; Calculate 0-based index
    LDR     r3, =weight          ; Load weight array address
    LSLS    r2, r2, #2           ; Multiply index by 4 (word size)
    LDR     r3, [r3, r2]         ; Load weight of the current item

    LDR     r2, [r7, #8]         ; Load remaining capacity
    SUBS    r2, r2, r3           ; Subtract current item weight from capacity

    LDR     r3, =dp              ; Load dp array address
    LSLS    r2, r2, #2           ; Multiply capacity by 4 (word size)
    LDR     r2, [r3, r2]         ; Load dp[remaining capacity]

    LDR     r3, [r7, #12]        ; Load current item index
    SUBS    r1, r3, #1           ; Calculate 0-based index
    LDR     r3, =profit          ; Load profit array address
    LSLS    r1, r1, #2           ; Multiply index by 4 (word size)
    LDR     r3, [r3, r1]         ; Load profit of the current item
    ADDS    r3, r2, r3           ; Add profit to dp value

    MOVS    r1, r3               ; Store result in r1
    BL      max                  ; Call max function to get max value

    LDR     r3, =dp              ; Load dp array address
    LDR     r2, [r7, #8]         ; Load remaining capacity
    LSLS    r2, r2, #2           ; Multiply capacity by 4 (word size)
    STR     r0, [r3, r2]         ; Store max value in dp array

skipCurrentItem
    LDR     r3, [r7, #8]         ; Load remaining capacity
    SUBS    r3, r3, #1           ; Decrease capacity by 1
    STR     r3, [r7, #8]         ; Update remaining capacity
    CMP     r3, #0               ; Check if capacity is zero
    BGE     knapSackInnerLoopStart ; If not, continue inner loop

    LDR     r3, [r7, #12]        ; Load current item index
    ADDS    r3, r3, #1           ; Increment item index
    STR     r3, [r7, #12]        ; Update current item index
    LDR     r2, [r7]             ; Load total number of items
    CMP     r2, r3               ; Compare item index with total number of items
    BGE     knapSackOuterLoop    ; If not all items are processed, continue outer loop

    LDR     r3, =dp              ; Load dp array address
    LDR     r2, [r7, #4]         ; Load knapsack capacity
    LSLS    r2, r2, #2           ; Multiply capacity by 4 (word size)
    LDR     r3, [r3, r2]         ; Load final result from dp array
    MOVS    r0, r3               ; Store result in r0

    MOV     sp, r7               ; Restore stack pointer
    ADD     sp, sp, #16          ; Deallocate stack space
    POP     {r7, pc}             ; Restore frame pointer and return
    
    ENDFUNC                      ; Mark end of function
    
    END                          ; End of program
