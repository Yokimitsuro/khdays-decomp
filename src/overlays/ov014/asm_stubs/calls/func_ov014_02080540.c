extern void strncpy(void);
extern void func_ov002_020769b0(void);
extern void func_ov014_02080230(void);
extern void func_ov014_02080244(void);
extern void func_ov014_02080264(void);
extern void func_ov014_02080268(void);
extern void func_ov014_02080340(void);
extern void func_ov014_020803c0(void);
extern void func_ov014_02080430(void);
extern void func_ov014_02080444(void);
extern void func_ov014_02080458(void);
extern void func_ov014_02080460(void);

asm void func_ov014_02080540(void)
{
    push    {r3, r4, r5, lr}
    add     r2, r0, #0
    mov     r0, #0x70
    add     r5, r1, #0
    add     r1, r0, #0
    add     r1, #0xc8
    bl      func_ov002_020769b0
    add     r4, r0, #0
    ldr     r1, [r5, #0]
    add     r0, #0x58
    mov     r2, #0x10
    bl      strncpy
    ldr     r0, [r5, #4]
    ldr     r1, [pc, #0x44]
    str     r0, [r4, #0x68]
    ldr     r0, [r5, #8]
    str     r0, [r4, #0x6c]
    mov     r0, #0
    str     r0, [r4, #0]
    str     r0, [r4, #4]
    str     r1, [r4, #8]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0xc]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0x10]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0x14]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0x18]
    ldr     r1, [pc, #0x38]
    str     r0, [r4, #0x1c]
    str     r1, [r4, #0x20]
    ldr     r1, [pc, #0x34]
    str     r1, [r4, #0x24]
    ldr     r1, [pc, #0x34]
    str     r1, [r4, #0x28]
    ldr     r1, [pc, #0x34]
    str     r1, [r4, #0x2c]
    str     r0, [r4, #0x38]
    str     r0, [r4, #0x44]
    ldr     r0, [pc, #0x30]
    mov     r1, #0x12
    str     r0, [r4, #0x3c]
    add     r0, r4, #0
    add     r0, #0x4c
    strh    r1, [r0, #0]
    add     r0, r4, #0
    pop     {r3, r4, r5, pc}
    dcd     func_ov014_02080230
    dcd     func_ov014_02080264
    dcd     func_ov014_02080340
    dcd     func_ov014_02080244
    dcd     func_ov014_02080268
    dcd     func_ov014_020803c0
    dcd     func_ov014_02080430
    dcd     func_ov014_02080444
    dcd     func_ov014_02080458
    dcd     func_ov014_02080460
}
