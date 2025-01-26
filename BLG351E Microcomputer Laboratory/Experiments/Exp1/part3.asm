Setup 	mov.b #11111111b,&P2DIR
			mov.b #00000000b,&P1DIR
			mov.b #00000000b,&P2OUT
			mov.b #00000001b , R6
			mov.b #0d , R8

Mainloop1 	bis.b R6 , &P2OUT
			inc R8
			rla R6
			mov.w #00500000 , R15
L1			dec.w R15
			jnz L1
Button		bit.b #10000000, &P1IN
			jnz Off
			cmp #8d , R8
			jne Mainloop1
			jmp Setup 
Off