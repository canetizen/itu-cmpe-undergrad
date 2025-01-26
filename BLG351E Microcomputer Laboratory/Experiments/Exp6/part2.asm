MainProgram
            call #ConvertDisplayRoutine    ; Call ConvertDisplayRoutine to handle display updates.
            jmp MainProgram                ; Return to the main program loop.

ConvertDisplayRoutine
            call #NumericConversionRoutine ; Call NumericConversionRoutine to convert time values to digits.
            mov.b @r4, &P1OUT              ; Move the first digit to output port P1.
            mov.b #08h, &P2OUT             ; Select the display segment for the first digit.
            nop                             ; No operation (timing adjustment).
            nop                             ; No operation (timing adjustment).
            clr &P1OUT                     ; Clear port P1 after displaying the digit.
            clr &P2OUT                     ; Clear port P2 after displaying the digit.
            mov.b @r5, &P1OUT              ; Move the second digit to output port P1.
            mov.b #04h, &P2OUT             ; Select the display segment for the second digit.
            nop                             ; No operation (timing adjustment).
            nop                             ; No operation (timing adjustment).
            clr &P1OUT                     ; Clear port P1 after displaying the digit.
            clr &P2OUT                     ; Clear port P2 after displaying the digit.
            mov.b @r6, &P1OUT              ; Move the third digit to output port P1.
            mov.b #02h, &P2OUT             ; Select the display segment for the third digit.
            nop                             ; No operation (timing adjustment).
            nop                             ; No operation (timing adjustment).
            clr &P1OUT                     ; Clear port P1 after displaying the digit.
            clr &P2OUT                     ; Clear port P2 after displaying the digit.
            mov.b @r7, &P1OUT              ; Move the fourth digit to output port P1.
            mov.b #01h, &P2OUT             ; Select the display segment for the fourth digit.
            nop                             ; No operation (timing adjustment).
            nop                             ; No operation (timing adjustment).
            clr &P1OUT                     ; Clear port P1 after displaying the digit.
            clr &P2OUT                     ; Clear port P2 after displaying the digit.
            ret                            ; Return to the calling function.

;-------------------------------------------------------------------------------
; Button Interrupt Handler
;-------------------------------------------------------------------------------
ButtonInterruptHandler
            push r15                       ; Save register r15 on the stack.
            mov.b &P2IFG, r15              ; Read the interrupt flag register for port P2.

            bit.b #040h, r15               ; Check if the reset button was pressed.
            jnz HandleResetRoutine         ; If reset, jump to HandleResetRoutine.

            bit.b #020h, r15               ; Check if the pause button was pressed.
            jnz HandlePauseRoutine         ; If pause, jump to HandlePauseRoutine.

            bit.b #080h, r15               ; Check if the start button was pressed.
            jnz HandleStartRoutine         ; If start, jump to HandleStartRoutine.

ExitISR    clr &P2IFG                     ; Clear interrupt flags for port P2.
            pop r15                        ; Restore register r15.
            reti                           ; Return from interrupt.

HandleResetRoutine
            mov.b #00h, &timer_sec         ; Reset the seconds timer to 0.
            mov.b #00h, &timer_cs          ; Reset the centiseconds timer to 0.
            bic.b #01h, &control_reg       ; Disable the control register.
            jmp ExitISR                    ; Jump to ISR exit.

HandlePauseRoutine
            bic.b #01h, &control_reg       ; Pause the timer by disabling the control register.

            bit.b #0A0h, &P2IN             ; Check if the best time button is pressed.
            jnz RecordBestTimeRoutine      ; If pressed, jump to RecordBestTimeRoutine.
            jz HandlePauseRoutine          ; If not pressed, remain in pause state.
            jmp ExitISR                    ; Jump to ISR exit.

HandleStartRoutine
            mov.b #01h, &control_reg       ; Start the timer by enabling the control register.
            jmp ExitISR                    ; Jump to ISR exit.

RecordBestTimeRoutine
            mov.b &timer_sec, r14          ; Load current seconds into register r14.
            cmp.b &record_sec, r14         ; Compare current seconds with recorded best seconds.
            jl StoreRecordRoutine          ; If less, jump to StoreRecordRoutine.
            jmp ExitISR                    ; If not, jump to ISR exit.

            mov.b &timer_cs, r14           ; Load current centiseconds into register r14.
            cmp.b &record_cs, r14          ; Compare current centiseconds with recorded best centiseconds.
            jhs ExitISR                    ; If greater or equal, jump to ISR exit.

StoreRecordRoutine
            mov.b &timer_sec, &record_sec  ; Store the current seconds as the best seconds.
            mov.b &timer_cs, &record_cs    ; Store the current centiseconds as the best centiseconds.
            jmp ExitISR                    ; Jump to ISR exit.

;-------------------------------------------------------------------------------
; Timer Interrupt Service Routine
;-------------------------------------------------------------------------------
TimerInterruptHandler
            dint                           ; Disable interrupts temporarily.
            push r15                       ; Save register r15 on the stack.

            cmp #00h, &control_reg         ; Check if the timer is active.
            jz EndTimerRoutine             ; If not active, jump to end of timer routine.

            add.b #1b, &timer_cs           ; Increment centiseconds.
            mov.b &timer_cs, r15           ; Load the updated centiseconds into r15.
            bic.b #0F0h , r15              ; Mask higher bits of centiseconds.
            cmp #0Ah, r15                  ; Check if centiseconds reached 10.
            jz IncrementSecondsRoutine     ; If so, jump to IncrementSecondsRoutine.
            jmp EndTimerRoutine            ; Otherwise, jump to end of timer routine.

IncrementSecondsRoutine
            add.b #010h , &timer_cs        ; Increment the tens place of centiseconds.
            bic.b #00Fh, &timer_cs         ; Clear the lower bits of centiseconds.
            mov.b &timer_cs, r15           ; Load updated centiseconds into r15.
            cmp #0A0h, r15                 ; Check if centiseconds reached 100.
            jz SecondCycleRoutine          ; If so, jump to SecondCycleRoutine.
            jmp EndTimerRoutine            ; Otherwise, jump to end of timer routine.

SecondCycleRoutine
            add.b #001h , &timer_sec       ; Increment seconds.
            bic.b #0FFh , &timer_cs        ; Reset centiseconds.
            mov.b &timer_sec, r15          ; Load updated seconds into r15.
            cmp #0Ah, r15                  ; Check if seconds reached 10.
            jz RolloverCheckRoutine        ; If so, jump to RolloverCheckRoutine.
            jmp EndTimerRoutine            ; Otherwise, jump to end of timer routine.

RolloverCheckRoutine
            add.b #010h , &timer_sec       ; Increment the tens place of seconds.
            bic.b #00Fh, &timer_sec        ; Clear the lower bits of seconds.
            mov.b &timer_sec, r15          ; Load updated seconds into r15.
            cmp #0A0h, r15                 ; Check if seconds reached 100.
            jz ResetRoutine                ; If so, jump to ResetRoutine.

EndTimerRoutine
            pop r15                        ; Restore register r15.
            eint                           ; Enable interrupts.
            reti                           ; Return from interrupt.

;-------------------------------------------------------------------------------
; Numeric Conversion Routine
;-------------------------------------------------------------------------------
NumericConversionRoutine
            push r14                       ; Save register r14 on the stack.

            mov.b &timer_cs, r14           ; Load centiseconds into r14.
            bic.b #0F0h, r14               ; Mask higher bits.
            mov.w #digit_map, r4           ; Load the digit map for units place.
            add.w r14, r4                  ; Calculate the address for the units digit.

            mov.b &timer_cs, r14           ; Load centiseconds into r14 again.
            rra.b r14                      ; Shift right to isolate tens place.
            rra.b r14
            rra.b r14
            rra.b r14
            bic.b #0F0h, r14               ; Mask higher bits.
            mov.w #digit_map, r5           ; Load the digit map for tens place.
            add.w r14, r5                  ; Calculate the address for the tens digit.

            mov.b &timer_sec, r14          ; Load seconds into r14.
            bic.b #0F0h, r14               ; Mask higher bits.
            mov.w #digit_map, r6           ; Load the digit map for units place.
            add.w r14, r6                  ; Calculate the address for the units digit.

            mov.b &timer_sec, r14          ; Load seconds into r14 again.
            rra.b r14                      ; Shift right to isolate tens place.
            rra.b r14
            rra.b r14
            rra.b r14
            bic.b #0F0h, r14               ; Mask higher bits.
            mov.w #digit_map, r7           ; Load the digit map for tens place.
            add.w r14, r7                  ; Calculate the address for the tens digit.

            pop r14                        ; Restore register r14.
            ret                            ; Return to the calling function.

;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack

            .sect   ".reset"               ; Define reset vector.
            .short  ResetRoutine           ; Reset handler routine.

            .sect   ".int09"               ; Define timer interrupt vector.
            .short  TimerInterruptHandler  ; Timer interrupt handler routine.

            .sect   ".int03"               ; Define button interrupt vector.
            .short  ButtonInterruptHandler ; Button interrupt handler routine.
