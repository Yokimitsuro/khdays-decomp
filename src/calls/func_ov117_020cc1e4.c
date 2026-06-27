extern void func_ov107_020cb040(void);
extern void func_ov117_020cc1c8(void);
extern void func_ov107_020c7500(void);

asm void func_ov117_020cc1e4(void)
{
    stmfd   sp!, {r3, r4, r5, r6, lr}
    sub     sp, sp, #4
    mov     r5, r1
    ldrb    r1, [r5, #2]
    mov     r6, r0
    mov     r4, r2
    cmp     r1, #5
    bne     _L5c
    ldrb    r1, [r5, #3]
    cmp     r1, #0
    bne     _L5c
    ldr     r1, [r6, #0x390]
    cmp     r1, #0
    bne     _L58
    add     r1, r6, #0xa0
    str     r1, [sp]
    mov     r1, #0x120
    mov     r2, #5
    mov     r3, #1
    bl      func_ov107_020cb040
    str     r0, [r6, #0x390]
    b       _L5c
_L58:
    bl      func_ov117_020cc1c8
_L5c:
    mov     r0, r6
    mov     r1, r5
    mov     r2, r4
    bl      func_ov107_020c7500
    add     sp, sp, #4
    ldmfd   sp!, {r3, r4, r5, r6, pc}
}
