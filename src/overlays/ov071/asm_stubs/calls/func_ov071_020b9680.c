extern void func_ov071_020b9940(void);
extern void func_0201571c(void);
extern void func_01ff9f00(void);
extern void func_020279e0(void);

asm void func_ov071_020b9680(void)
{
    stmfd   sp!, {r4, r5, r6, lr}
    ldrb    r0, [r0, #0x694]
    mov     r6, r1
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    ldmeqfd sp!, {r4, r5, r6, pc}
    add     r5, r6, #0x118
    mov     r4, #0
_loop:
    mov     r0, r5
    bl      func_ov071_020b9940
    add     r4, r4, #1
    cmp     r4, #6
    add     r5, r5, #0x110
    blt     _loop
    ldr     r0, [r6]
    cmp     r0, #1
    ldmnefd sp!, {r4, r5, r6, pc}
    bl      func_0201571c
    add     r1, r6, #0x8c
    mov     r0, #0x17
    mov     r2, #0xc
    bl      func_01ff9f00
    add     r0, r6, #0x2c
    bl      func_020279e0
    ldmfd   sp!, {r4, r5, r6, pc}
}
