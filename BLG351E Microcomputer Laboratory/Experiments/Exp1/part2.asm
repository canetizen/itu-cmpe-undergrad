Setup 	mov.b #11111111b,&P1DIR
			mov.b #11111111b,&P2DIR
			mov.b #00000000b,&P1OUT
			mov.b #00000000b,&P2OUT
			mov.b #00000001b , R6
			mov.b #00000001b , R7
			mov.b #0d , R8
			mov.b #0d , R9

Mainloop1 	cmp #0d , R9
			jeq LEFT
			mov.b R7, &P2OUT
			mov.b #00000000b, &P1OUT
			mov.b #0d, R9
			jmp RIGHT
LEFT		mov.b R6, &P1OUT
			mov.b #00000000b, &P2OUT
			inc R9
RIGHT		inc R8
			rla R6
			rla R7
			mov.w #00500000 , R15
L1			dec.w R15
			jnz L1
			cmp #8d , R8
			jeq Setup 
			jmp Mainloop1