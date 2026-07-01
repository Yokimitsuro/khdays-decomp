extern void func_ov081_020b953c(void *p);

asm void func_ov081_020b92dc(void *r0, void *r1)
{
    stmfd   sp!, {r3, r4, r5, lr}
    add     r5, r1, #0x14
    mov     r4, #0
_loop:
    mov     r0, r5
    bl      func_ov081_020b953c
    add     r4, r4, #1
    cmp     r4, #7
    add     r5, r5, #0x10c
    blt     _loop
    ldmfd   sp!, {r3, r4, r5, pc}
}
