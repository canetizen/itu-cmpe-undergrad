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
			
;COPY ARRAY			
		MOVS	r3,#ArraySize					;Load array size
		MOVS 	r0,#0							;i=0 as index value
		LDR 	r1,=y_array						;Load start address of the allocated space for y
		LDR 	r2,=x_array						;Load start address of x
Copy	CMP		r0,r3							;Check i<array_size
		BGE		endcopy							;if not finish loop
		LDR		r5,[r2,r0]						;temp = x[i]
		STR 	r5,[r1,r0]						;x[i] = temp
		adds 	r0,r0,#4						;i=i+4 for word.
		B		Copy							;End of the loop, jump start point

;BUBBLE SORT PART
endcopy MOVS 	r0,#0							;i=0 as index value
		MOVS	r3,#ArraySize					;Load array size
		SUBS	r3,r3,#4						;size=SIZE-1
		LDR 	r2,=y_array						;Load start address of the allocated space for y
L1		CMP		r0,r3							;Check i<array_size
		BGE		stop							;if not finish loop
		MOVS	r1,#0							;j=1 as second index
		MOVS	r4,r3							;cond=size
		SUBS	r4,r4,r0						;cond = size-1
L2		CMP		r1,r4							;check j< cond
		BGE		EndL2							;if j >= cond, finish inner loop 
		LDR		r5,[r2,r1]						;firstval = y[j]
		ADDS	r1,r1,#4						;j=j+4
		LDR		r6,[r2,r1]						;secondval = j[i]
		CMP		r5,r6							;check firstval > secondval
		BLE		L2								;if firstval<=second then jump L1
		STR		r5,[r2,r1]						;y[j]=firstval
		SUBS	r1,r1,#4						;j=j-4
		STR		r6,[r2,r1]						;y[j]=secondval
		ADDS	r1,r1,#4						;j=j+4
		B		L2								;Go to L2
EndL2	ADDS	r0,r0,#4						;i=i+4 for word.
		B		L1								;Go to L1
		
stop	B stop									;Infinite loop
		ALIGN
		ENDFUNC

x_array DCD     12,20,25,60,15,53,17,65,22,1	;write x array to code memory
x_end
		ENDs