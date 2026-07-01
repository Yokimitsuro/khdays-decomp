extern void func_ov117_020cc1c8(void *);
extern void func_ov107_020c7da4(void *);

asm void func_ov117_020cc258(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    bl      func_ov117_020cc1c8
    mov     r0, r4
    bl      func_ov107_020c7da4
    ldmfd   sp!, {r4, pc}
}
