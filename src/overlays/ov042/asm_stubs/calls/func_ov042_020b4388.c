extern int func_ov022_02095524(void *r0);
extern void func_ov042_020b4628(void *r0, int r1);

asm void func_ov042_020b4388(void *r0, void *r1, int r2)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r5, r1
    ldr     r1, [r5]
    mov     r4, r2
    cmp     r1, #0
    beq     _L_after
    ldr     r2, [r0, #0x464]
    ldr     r1, [r0, #0x468]
    and     r2, r2, #0x10000
    and     r1, r1, #0
    cmp     r1, #0
    cmpeq   r2, #0
    bne     _L_after
    add     r0, r0, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095524
    cmp     r0, #0
    moveq   r0, #0
    streq   r0, [r5]
_L_after:
    add     r6, r5, #0x14
    mov     r5, #0
_L_loop:
    mov     r0, r6
    mov     r1, r4
    bl      func_ov042_020b4628
    add     r5, r5, #1
    cmp     r5, #7
    add     r6, r6, #0x10c
    blt     _L_loop
    ldmfd   sp!, {r4, r5, r6, pc}
}
