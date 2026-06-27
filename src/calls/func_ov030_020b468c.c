extern void func_ov030_020b43c0(void *p);
extern void func_ov030_020b4800(void *p);
extern void func_0202aa9c(void *p);

asm void func_ov030_020b468c(void *r0)
{
    stmdb   sp!, {r3, r4, r5, r6, r7, lr}
    mov     r4, r0
    ldr     r5, [r4, #0xdb4]
    ldrb    r0, [r5, #0x694]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
    add     r7, r4, #0x234
    mov     r6, #0
_L_24:
    mov     r0, r7
    bl      func_ov030_020b43c0
    add     r6, r6, #1
    cmp     r6, #8
    add     r7, r7, #0x170
    blt     _L_24
    mov     r0, r4
    bl      func_ov030_020b4800
    ldr     r0, [r4, #0x14]
    cmp     r0, #1
    ldmneia sp!, {r3, r4, r5, r6, r7, pc}
    add     r0, r5, #0x8c
    add     r0, r0, #0x400
    add     r3, r4, #0xbc
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    add     r0, r4, #0x18
    bl      func_0202aa9c
    ldmia   sp!, {r3, r4, r5, r6, r7, pc}
}
