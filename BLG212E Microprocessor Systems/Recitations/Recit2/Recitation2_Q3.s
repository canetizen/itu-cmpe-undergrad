ArraySize   EQU	0x28							;Array size = 40

		AREA     My_Array, DATA, READWRITE		;Define this part will write in data area
		ALIGN	
y_array SPACE    ArraySize						;Allocate space from memory for y
y_end

		AREA copy_array, code, readonly			;Define this part will write as code
		ENTRY
		THUMB
		ALIGN 
__main	FUNCTION
		EXPORT __main
			
			
		MOVS	r3,#ArraySize					;Load array size
		MOVS 	r0,#0							;i=0 as index value
		LDR 	r1,=y_array						;Load start address of the allocated space for y
		LDR 	r2,=x_array						;Load start address of x
Copy	CMP		r0,r3							;Check i<array_size
		BGE		stop							;if not finish loop
		LDR		r5,[r2,r0]						;temp = x[i]
		STR 	r5,[r1,r0]						;x[i] = temp
		adds 	r0,r0,#4						;i=i+4 for word.
		B		Copy							;End of the loop, jump start point
stop	B stop									;Infinite loop
		ALIGN
		ENDFUNC

x_array DCD     12,20,25,60,15,53,17,65,22,1	;write x array to code memory
x_end
		END