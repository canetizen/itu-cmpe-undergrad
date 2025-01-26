SetupGPIO         mov.b #00000000b, &P1DIR       ; Set P1 pins as input
                  mov.b #11111111b, &P2DIR       ; Set P2 pins as output
                  mov.b #00000000b, &P1OUT       ; Initialize P1 output as low
                  mov.b #00000010b, &P2OUT       ; Initialize P2 output to 0x02
                  mov.b #00000000b, &P1IN        ; Initialize P1 input

MainLoop          bit.b #00010000b, &P1IN        ; Check if a specific bit in P1IN is set (button pressed)
                  jnz HandleChange               ; If set, jump to handle the change

ContinueLoop      jmp MainLoop                   ; Continue looping

HandleChange      cmp #00000010b, &P2OUT        ; Check if P2OUT is currently 0x02
                  jeq SetTo3                     ; If true, jump to set output to 0x03
                  jmp SetTo2                     ; Otherwise, set output to 0x02

SetTo2            mov.b #00000010b, &P2OUT       ; Set P2OUT to 0x02
                  jmp WaitForRelease             ; Jump to button release handling

SetTo3            mov.b #00000100b, &P2OUT       ; Set P2OUT to 0x04
                  jmp WaitForRelease             ; Jump to button release handling

WaitForRelease    mov.w #00050000, R15          ; Load R15 with delay value for debounce
DebounceDelay     dec.w R15                      ; Decrement R15
                  jnz DebounceDelay              ; Wait until R15 reaches zero (debounce delay)

                  bit.b #00010000b, &P1IN        ; Check if the button is still pressed
                  jnz WaitForRelease             ; If pressed, wait until release
                  jmp ContinueLoop               ; Go back to main loop
