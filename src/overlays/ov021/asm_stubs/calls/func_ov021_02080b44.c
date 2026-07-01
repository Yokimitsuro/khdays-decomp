extern char data_ov021_02080f40[];
extern void func_ov002_020769b0(void);
extern void func_ov021_02080540(void);
extern void func_ov021_02080600(void);
extern void func_ov021_02080650(void);
extern void func_ov021_02080660(void);
extern void func_ov021_02080738(void);
extern void strncpy(void);

asm void func_ov021_02080b44(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r1, #0
    mov     r1, #0xb
    add     r2, r0, #0
    mov     r0, #0x78
    lsl     r1, r1, #6
    bl      func_ov002_020769b0
    add     r4, r0, #0
    ldr     r0, [pc, #0x60]
    mov     r1, #0
    str     r4, [r0, #0]
    add     r0, r4, #0
    add     r0, #0x58
    strb    r1, [r0, #0]
    add     r0, r4, #0
    ldr     r1, [r5, #0]
    add     r0, #0x58
    mov     r2, #0x10
    bl      strncpy
    add     r0, r4, #0
    mov     r1, #0
    add     r0, #0x68
    strb    r1, [r0, #0]
    add     r0, r4, #0
    ldr     r1, [r5, #4]
    add     r0, #0x68
    mov     r2, #0x10
    bl      strncpy
    mov     r1, #0
    str     r1, [r4, #0]
    ldr     r0, [pc, #0x34]
    str     r1, [r4, #4]
    str     r0, [r4, #8]
    ldr     r0, [pc, #0x30]
    str     r0, [r4, #0xc]
    ldr     r0, [pc, #0x30]
    str     r0, [r4, #0x10]
    ldr     r0, [pc, #0x30]
    str     r0, [r4, #0x14]
    ldr     r0, [pc, #0x30]
    str     r0, [r4, #0x18]
    str     r1, [r4, #0x1c]
    str     r1, [r4, #0x20]
    str     r1, [r4, #0x24]
    str     r1, [r4, #0x28]
    str     r1, [r4, #0x2c]
    str     r1, [r4, #0x38]
    str     r1, [r4, #0x44]
    add     r0, r4, #0
    str     r1, [r4, #0x3c]
    mov     r1, #0x1f
    add     r0, #0x4c
    strh    r1, [r0, #0]
    add     r0, r4, #0
    pop     {r3, r4, r5, pc}
    dcd     data_ov021_02080f40
    dcd     func_ov021_02080540
    dcd     func_ov021_02080650
    dcd     func_ov021_02080738
    dcd     func_ov021_02080600
    dcd     func_ov021_02080660
}
