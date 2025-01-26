; BLG 212E Homework 2
; Mustafa Can Caliskan
; 150200097

		AREA    bubbleSort, CODE, READONLY
		THUMB
		ALIGN

		EXPORT  ft_lstsort_asm

ft_lstsort_asm FUNCTION                        ; Define the bubble sort function 'ft_lstsort_asm'
    PUSH    {R0-R1, LR}                       ; Save registers R0, R1, and the link register (LR) to the stack to preserve their values

    MOVS    R2, #0                            ; Clear R2 register (used for the swap tracker), indicating no swaps initially
    SUB     SP, SP, #4                        ; Adjust the stack pointer to allocate space for a swap tracker (4 bytes)
    STR     R2, [SP]                          ; Store the initial value of 0 (no swaps) into the allocated stack space

traverseNodes                                   ; Label for traversing the list nodes
    LDR     R3, [SP, #4]                      ; Load the pointer to the head of the list into register R3
    LDR     R4, [R3]                          ; Dereference head pointer to get the current node pointer in R4
    MOVS    R6, #0                            ; Initialize R6 as 0 to track the previous node pointer (null initially)
    LDR     R7, [SP]                          ; Load the swap tracker value from the stack into R7
    CMP     R4, R7                             ; Compare the current node pointer (R4) with the swap tracker (R7)
    BEQ     finalizeNodes                      ; If they are equal, list is sorted, so jump to finalize the sorting process
    LDR     R5, [R4, #4]                      ; Load the next node pointer from the current node (R4) into R5
    CMP     R5, R7                             ; Compare the next node pointer (R5) with the swap tracker
    BEQ     finalizeNodes                      ; If the next node is equal to the swap tracker, finish sorting

processNodes                                  ; Label to process nodes in each pass of the bubble sort
    LDR     R5, [R4, #4]                      ; Load the next node pointer (R5) from the current node (R4)
    LDR     R2, [SP]                          ; Load the swap tracker value (0 or 1) from the stack into R2
    CMP     R5, R2                             ; Compare the next node pointer (R5) with the swap tracker
    BEQ     finalizeNodes                      ; If end of the current pass is reached, finalize the sorting
    LDR     R0, [R4, #0]                      ; Load the current node's data (R0) from the node (R4)
    LDR     R1, [R5, #0]                      ; Load the next node's data (R1) from the next node (R5)
    LDR     R2, [SP, #8]                      ; Load the comparator function pointer from the stack into R2
    BLX     R2                                ; Branch to the comparator function (R2) and perform comparison
    CMP     R0, #0                            ; Compare the result of the comparator with 0 (indicating whether swap is needed)
    BNE     skipSwap                          ; If result is not equal to 0, do not swap, continue to next iteration

    CMP     R6, #0                            ; Check if this is the first node (R6 is 0 if no previous node exists)
    BNE     updateMiddle                      ; If not, update the middle of the list
    LDR     R3, [SP, #4]                      ; Load the head pointer from the stack into R3
    STR     R5, [R3]                          ; Update the head pointer to point to the next node (R5) after swap
    B       linkNodes                         ; Jump to linkNodes to perform the link update after the swap

updateMiddle                                 ; Label to update links in the middle of the list (non-head nodes)
    STR     R5, [R6, #4]                      ; Update the 'next' pointer of the previous node (R6) to point to the swapped node (R5)

linkNodes                                   ; Label for linking nodes after a swap
    SUB     SP, SP, #4                        ; Allocate space on the stack for the current node to store it temporarily
    STR     R4, [SP, #0]                      ; Store the current node (R4) pointer in the allocated space
    MOV     R4, R5                            ; Move to the next node (R5) after the swap
    LDR     R1, [R4, #4]                      ; Load the pointer to the node after the next node (R1) into R1
    LDR     R0, [SP, #0]                      ; Load the stored current node pointer (R4) from the stack into R0
    STR     R1, [R0, #4]                      ; Set the next node's 'next' pointer to the node after the swapped node (R1)
    STR     R0, [R4, #4]                      ; Set the swapped node's 'next' pointer to point to the current node (R0)
    ADD     SP, SP, #4                        ; Restore the stack pointer by deallocating the 4 bytes used for current node storage
    MOV     R6, R4                            ; Update the previous node pointer (R6) to the current node (R4)

    B       continueLoop                      ; Jump to the next iteration of the loop to continue processing nodes

skipSwap                                    ; Label to skip the swap if not needed
    MOV     R6, R4                            ; Update the previous node pointer (R6) to the current node (R4)

continueLoop                                 ; Label to continue the loop in bubble sort
    CMP     R0, #0                            ; Compare the current node data (R0) with 0 (indicating the end of the list)
    BEQ     processNodes                       ; If end of the list, jump to process nodes to continue the pass
    MOV     R4, R5                            ; Move to the next node (R5) to continue the loop

    B       processNodes                       ; Jump back to the processNodes label to continue processing the list

finalizeNodes                                ; Label to finalize the sorting process once all passes are done
    STR     R4, [SP]                          ; Store the final node pointer (R4) into the stack as the last node

checkSortStatus                              ; Label to check if another pass is needed (checking if sorting is complete)
    LDR     R2, [SP]                          ; Load the swap tracker value (0 or 1) from the stack into R2
    LDR     R7, [SP, #4]                      ; Load the head pointer again (R7) from the stack
    LDR     R7, [R7]                          ; Dereference the head pointer (R7) to access the first node
    CMP     R2, R7                            ; Compare the swap tracker with the head pointer to see if sorting is still required
    BNE     traverseNodes                     ; If they are not equal, the list may still need sorting, so loop back to traverseNodes

    ADD     SP, SP, #4                        ; Restore the stack pointer by deallocating space used for the swap tracker
    POP     {R0-R1, PC}                       ; Restore registers R0, R1 and the program counter (PC) to return from the function
    ENDFUNC                                    ; End of the function
    END                                       ; End of the assembly code section
