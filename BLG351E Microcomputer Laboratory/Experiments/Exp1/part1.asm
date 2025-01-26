Setup 	mov.b #11111111b,&P1DIR
			mov.b #11111111b,&P2DIR
			mov.b #00000000b,&P1OUT
			mov.b #00000000b,&P2OUT
			mov.b #00001000b , R6
			mov.b #00010000b , R7
			mov.b #0d , R8

Mainloop1 	bis.b R7 , &P2OUT
			inc R8
			rla R7
			mov.w #00500000 , R15
L1			dec.w R15
			jnz L1
			cmp #4d , R8
			jeq Mainloop2
			jmp Mainloop1


Mainloop2 	mov.b #00000000b,&P2OUT
			bis.b R6 , &P1OUT
			dec.w R8
			rra R6
			mov.w #00500000 , R15
L2			dec.w R15
			jnz L2
			cmp #0d , R8
			jeq Setup 
			jmp Mainloop2
