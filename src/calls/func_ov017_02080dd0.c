extern void func_02021980(void);
extern void func_ov002_0207679c(void);
extern void func_ov017_02080a68(void);

asm void func_ov017_02080dd0(void)
{
    push    {r4, r5, r6, lr}
    add     r5, r1, #0
    add     r6, r0, #0
    bl      func_02021980
    add     r5, #8
    add     r4, r0, #0
    add     r0, r6, #0
    add     r1, r5, #0
    bl      func_02021980
    add     r1, r0, #0
    lsl     r0, r4, #0x18
    lsl     r1, r1, #0x10
    lsr     r0, r0, #0x18
    lsr     r1, r1, #0x10
    bl      func_ov002_0207679c
    bl      func_ov017_02080a68
    mov     r0, #1
    pop     {r4, r5, r6, pc}
}
