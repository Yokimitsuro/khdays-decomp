extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_01fff8e8(void);
extern void func_01fff920(void);

asm void func_ov241_020d01bc(void *r0)
{
    stmfd   sp!, {r0, r1, r2, r3}
    stmfd   sp!, {r3, r4, lr}
    sub     sp, sp, #0x1c
    ldr     r0, [r0]
    add     r3, sp, #4
    ldr     r4, [r0, #4]
    add     r0, r0, #0x74
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    add     r0, sp, #0x2c
    add     r2, sp, #0x10
    mov     r1, r3
    bl      VEC_Subtract
    add     r0, sp, #0x10
    mov     r1, r0
    bl      func_01ff8d18
    ldr     r1, [sp, #0x38]
    sub     r0, r0, r1
    add     r1, sp, #0x10
    cmp     r0, #0
    movle   r0, #1
    mov     r2, r1
    bl      func_01ffa724
    mov     r0, #0
    str     r0, [sp]
    ldr     r0, [r4, #0x7c]
    add     r1, sp, #4
    add     r2, sp, #0x10
    mov     r3, #0x300
    bl      func_01fff8e8
    cmp     r0, #0
    beq     _try2
    ldr     r0, [r0, #8]
    cmp     r0, #0
    addeq   sp, sp, #0x1c
    moveq   r0, #0
    ldmeqfd sp!, {r3, r4, lr}
    addeq   sp, sp, #0x10
    bxeq    lr
_try2:
    ldr     r0, [r4, #0x7c]
    add     r1, sp, #4
    add     r2, sp, #0x10
    bl      func_01fff920
    cmp     r0, #0
    beq     _end
    ldr     r0, [r0, #8]
    cmp     r0, #0
    addeq   sp, sp, #0x1c
    moveq   r0, #0
    ldmeqfd sp!, {r3, r4, lr}
    addeq   sp, sp, #0x10
    bxeq    lr
_end:
    mov     r0, #1
    add     sp, sp, #0x1c
    ldmfd   sp!, {r3, r4, lr}
    add     sp, sp, #0x10
    bx      lr
}
