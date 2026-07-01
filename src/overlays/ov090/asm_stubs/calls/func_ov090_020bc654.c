extern char data_ov090_020bcbd4[];
extern char data_ov090_020bcc00[];
extern void func_0202a634(void);
extern void func_0202accc(void);

asm void func_ov090_020bc654(void)
{
    push    {r4, lr}
    ldr     r0, [pc, #0x48]
    ldr     r1, [pc, #0x48]
    ldr     r3, [r0, #0]
    ldr     r0, [pc, #0x48]
    mov     r2, #1
    add     r4, r3, r0
    mov     r0, #0
    str     r0, [r4, #0x24]
    str     r0, [r4, #0]
    str     r0, [r4, #0x10]
    str     r0, [r4, #0xc]
    ldrb    r3, [r3, #9]
    add     r0, r4, #0
    add     r0, #0x28
    add     r3, r3, #7
_L_0020:
    bl      func_0202a634
    mov     r2, #0x42
    add     r0, r4, #0
    mov     r1, #0
    lsl     r2, r2, #2
    add     r0, #0x28
    add     r2, r4, r2
    add     r3, r1, #0
_L_0032:
    bl      func_0202accc
    mov     r2, #0x42
    add     r0, r4, #0
    lsl     r2, r2, #2
    add     r0, #0x28
    mov     r1, #2
    add     r2, r4, r2
    mov     r3, #0
_L_0044:
    bl      func_0202accc
    pop     {r4, pc}
    mov     r8, r8
    dcd     data_ov090_020bcc00
    dcd     data_ov090_020bcbd4
    cmp     r4, #0xe4
    lsl     r0, r0, #0
}
