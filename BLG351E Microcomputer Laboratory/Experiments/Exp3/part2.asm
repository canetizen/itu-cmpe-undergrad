; Part2 Code.
; Mustafa Can Caliskan 150200097, Vedat Akgoz 150200009, Yusuf Sahin 150200016

.data
used_powers .space 20
index       .word 0
sum_powers  .word 0

        .text
        .global main
main:
        mov.w   #151, R4
        mov.w   #8, R5
        mov.w   R5, R6
        mov.w   R4, R7
        mov.w   #0, R8
        ; mov.w   #used_powers, R9
        mov.w   #1, R12
        mov.w   #0, R10


loop1:
        cmp.w   R6, R7
        jlo     loop1_end
        inc.w   R8
        add.w   R6, R6              ; C *= 2
        jmp     loop1

loop1_end:
        rra.w   R6              ; C /= 2 to set the correct upper limit
        dec.w   R8              ; Adjust exponent
loop2:

        cmp.w   R5, R7              ; Eğer D < B ise döngüden çık
        jl      loop2_end


        cmp.w   R6, R7
        jlo     loop1_end
        sub.w   R6, R7              ; D = D - C
        mov.w   R8, R14
sume_loop:


        dec.w   R14
        rla.w   R12
        cmp.w   #0, R14
        jne     sume_loop
        cmp.w   #1, R12
        jeq     enough
        add.w   R12, R10
        mov.w   #1, R12
enough:

        nop

skip_subtract:
        cmp.w   #0, R8
        jeq     skip_shift
skip_shift:
        jmp     loop2
loop2_end:
        nop