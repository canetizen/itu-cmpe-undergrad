SetupGPIO         mov.b #11111111b, &P2DIR       ; Set P2 pins as output
                  mov.b #11111110b, &P1DIR       ; Set P1 pins as input (except bit 0)
                  mov.b #00000000b, &P2OUT       ; Initialize P2 output to 0x00
                  mov.b #00000000b, &P1IN        ; Initialize P1 input

MainLoop          bit.b #00000001b, &P1IN        ; Check if bit 0 in P1IN is set (button pressed)
                  jnz IncrementCounter           ; If set, jump to increment the counter

ContinueLoop      jmp MainLoop                   ; Continue looping

IncrementCounter  mov.b counter, r4             ; Load current counter value into r4
                  cmp #00001111b, r4            ; Compare counter with 0x0F (15)
                  jeq ResetCounter               ; If equal, reset counter to 0
                  jmp IncrementByOne             ; Otherwise, increment counter by 1

ResetCounter      mov.b #00000000b, r4          ; Reset r4 to 0
                  mov.b r4, counter             ; Store reset value back into counter
                  mov.b r4, &P2OUT              ; Update P2 output to reflect reset value
                  jmp WaitForRelease            ; Jump to button release handling

IncrementByOne    inc r4                        ; Increment r4 by 1
                  mov.b r4, counter             ; Store incremented value back into counter
                  mov.b r4, &P2OUT              ; Update P2 output to reflect incremented value
                  jmp WaitForRelease            ; Jump to button release handling

WaitForRelease    mov.w #00050000, R15          ; Load R15 with delay value for debounce
DebounceDelay     dec.w R15                      ; Decrement R15
                  jnz DebounceDelay              ; Wait until R15 reaches zero (debounce delay)

                  bit.b #00000001b, &P1IN        ; Check if the button is still pressed
                  jnz WaitForRelease             ; If pressed, wait until release
                  jmp ContinueLoop               ; Go back to main loop

DataSection       .data                         ; Data section declaration
counter           .word 0x00                    ; Initialize counter variable to 0
