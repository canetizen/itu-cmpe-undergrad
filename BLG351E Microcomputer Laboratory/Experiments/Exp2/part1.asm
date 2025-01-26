INIT:
    bis.b #11111111b, &P1DIR
    bic.b #11111111b, &P1OUT
    mov.b #00000000b, &P2DIR

START:
    bit.b #10000000b, &P2IN
    jz START
    bis.b #00010000b, &P1OUT

END_LOOP:
    jmp END_LOOP
