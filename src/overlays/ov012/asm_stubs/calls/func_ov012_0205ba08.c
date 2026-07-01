extern void func_02021948(void);
extern void func_ov012_0205bb84(void);
extern void func_ov012_0205c224(void);
extern void func_ov012_0205c278(void);

asm void func_ov012_0205ba08(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      func_02021948
    add     r4, r0, #0
    mov     r0, #0x4a
    lsl     r0, r0, #2
    ldr     r0, [r5, r0]
    ldr     r0, [r0, #0xc]
    bl      func_ov012_0205bb84
    mov     r0, #0x4a
    lsl     r0, r0, #2
    ldr     r0, [r5, r0]
    add     r1, r4, #0
    ldr     r0, [r0, #0xc]
    bl      func_ov012_0205c224
    mov     r0, #0x4a
    lsl     r0, r0, #2
    ldr     r0, [r5, r0]
    ldr     r0, [r0, #0xc]
    bl      func_ov012_0205c278
    mov     r0, #1
    pop     {r3, r4, r5, pc}
}
