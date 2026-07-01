extern void func_ov028_0208aa54(void);
extern void func_ov028_0208aa08(void);

asm int func_ov028_0208aa78(void *r0, void *r1, void *r2, int r3)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub     sp, sp, #0x100
    mov     r7, r3
    tst     r7, #3
    mov     r10, r0
    mov     r9, r1
    mov     r8, r2
    addne   sp, sp, #0x100
    mvnne   r0, #0
    ldmneia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
    add     r0, sp, #0
    bl      func_ov028_0208aa54
    cmp     r7, #0
    mov     r4, #0
    bls     _L_end
    add     r11, sp, #0
_L_loop:
    mov     r0, r10
    add     r5, r9, r4
    add     r6, r8, r4
    bl      func_ov028_0208aa08
    ldrb    r1, [r9, r4]
    eor     r1, r1, r0
    mov     r0, r10
    strb    r1, [r8, r4]
    bl      func_ov028_0208aa08
    ldrb    r1, [r5, #1]
    add     r4, r4, #4
    cmp     r4, r7
    eor     r0, r1, r0
    strb    r0, [r6, #1]
    ldrb    r0, [r5, #2]
    ldrb    r0, [r11, r0]
    strb    r0, [r6, #2]
    ldrb    r0, [r5, #3]
    strb    r0, [r6, #3]
    blo     _L_loop
_L_end:
    mov     r0, #0
    add     sp, sp, #0x100
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
