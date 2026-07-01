extern void func_01fff774(void *arg, int b, int c);
extern void func_02016ae8(void *arg, int b, int c);

asm void func_ov034_020b51e0(void)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r6, r1
    mov     r1, #0
    mov     r3, #1
    mov     r2, r1
    add     r0, r6, #0x28
    str     r3, [r6, #0x24]
    bl      func_01fff774
    add     r0, r6, #0x28
    mov     r1, #2
    mov     r2, #0
    bl      func_01fff774
    mov     r0, #0x1000
    str     r0, [r6, #0xe0]
    str     r0, [r6, #0xdc]
    mov     r5, #0
    str     r0, [r6, #0xd8]
    mov     r4, r5
_loop:
    ldr     r0, [r6, #0xa0]
    mov     r1, r5
    mov     r2, r4
    bl      func_02016ae8
    add     r5, r5, #1
    cmp     r5, #7
    blt     _loop
    ldr     r0, [r6, #0xa0]
    mov     r1, #7
    mov     r2, #3
    bl      func_02016ae8
    ldr     r0, [r6, #0xa0]
    mov     r1, #8
    mov     r2, #3
    bl      func_02016ae8
    ldr     r0, [r6, #0xa0]
    mov     r1, #9
    mov     r2, #3
    bl      func_02016ae8
    ldmfd   sp!, {r4, r5, r6, pc}
}
