extern void func_02021980(void);
extern void func_02021994(void);
extern void func_02020400(void);
extern void func_ov002_0207679c(void);
extern void func_ov017_020804a4(void);

asm void func_ov017_02080bcc(void)
{
    push    {r4, r5, r6, r7, lr}
    sub     sp, #0xc
    add     r4, r1, #0
    add     r5, r0, #0
    bl      func_02021980
    add     r1, r4, #0
    add     r6, r0, #0
    add     r0, r5, #0
    add     r1, #8
    bl      func_02021980
    add     r1, r4, #0
    add     r7, r0, #0
    add     r0, r5, #0
    add     r1, #0x10
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #0]
    add     r0, r5, #0
    add     r1, #0x18
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #4]
    add     r0, r5, #0
    add     r1, #0x20
    bl      func_02021994
    add     r4, #0x28
    str     r0, [sp, #8]
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021980
    mov     r1, #0x5a
    lsl     r0, r0, #0x10
    lsl     r1, r1, #2
    bl      func_02020400
    lsl     r0, r0, #0x10
    lsr     r4, r0, #0x10
    lsl     r0, r6, #0x18
    lsl     r1, r7, #0x10
    lsr     r0, r0, #0x18
    lsr     r1, r1, #0x10
    bl      func_ov002_0207679c
    lsl     r2, r4, #0x10
    add     r1, sp, #0
    asr     r2, r2, #0x10
    bl      func_ov017_020804a4
    mov     r0, #1
    add     sp, #0xc
    pop     {r4, r5, r6, r7, pc}
}
