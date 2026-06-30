extern void func_02023588(void);
extern void func_ov002_0206e700(void);

asm void func_ov069_020b821c(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    ldr     r6, [pc, #0x2c]
    add     r7, r0, #0
    mov     r4, #0
    mov     r5, #9
_L_000a:
    add     r0, r5, #0
    bl      func_02023588
    cmp     r0, #0
    beq     _L_0016
    add     r4, r4, #1
_L_0016:
    add     r5, r5, #1
    cmp     r5, r6
    blt     _L_000a
    mov     r0, #1
    add     r1, r4, #0
    bl      func_ov002_0206e700
    cmp     r4, r7
    blo     _L_002c
    mov     r0, #1
    pop     {r3, r4, r5, r6, r7, pc}
_L_002c:
    mov     r0, #0
    pop     {r3, r4, r5, r6, r7, pc}
    lsl     r1, r1, #0x10
    lsl     r0, r0, #0
}
