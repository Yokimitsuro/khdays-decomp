extern void func_0202aef8(void);
extern void func_ov022_02091b48(void);
extern void func_ov022_02091540(void);
extern void func_ov022_02091d80(void);
extern int data_02041dc8;

asm void func_ov070_020b9810(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    sub     sp, sp, #0x18
    mov     r5, r1
    mov     r6, r0
    add     r0, r5, #0x28
    mov     r1, #0
    mov     r4, r2
    bl      func_0202aef8
    mov     r3, r0
    add     r0, r5, #0xcc
    sub     lr, r3, #0x9000
    add     ip, sp, #0xc
    ldmia   r0, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    ldr     r7, =data_02041dc8
    add     r3, sp, #0
    ldmia   r7, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r5, #4]
    add     r0, r0, r4
    str     r0, [r5, #4]
    ldr     r1, [sp, #0x10]
    ldr     r0, [sp, #4]
    sub     r1, r1, #0x5000
    add     r0, r0, #0xa000
    str     r1, [sp, #0x10]
    str     r0, [sp, #4]
    ldr     r0, [r5, #4]
    cmp     r0, lr
    bgt     _skip1
    mov     r0, r6
    mov     r1, r5
    mov     r2, ip
    bl      func_ov022_02091b48
_skip1:
    mov     r2, #4
    mov     r1, r4
    add     r0, r5, #0x28
    strb    r2, [r5, #2]
    bl      func_ov022_02091540
    cmp     r0, #0
    movne   r0, #3
    strneb  r0, [r5, #2]
    ldrsb   r0, [r5, #2]
    cmp     r0, #3
    bne     _end
    mov     r2, #0
    mov     r0, r6
    mov     r1, r5
    str     r2, [r5, #4]
    bl      func_ov022_02091d80
_end:
    mov     r0, #0
    add     sp, sp, #0x18
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
