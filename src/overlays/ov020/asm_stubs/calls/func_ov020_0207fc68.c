extern void *func_ov002_020769b0(int r0, int r1);
extern char *strncpy(char *dst, const char *src, int n);
extern int func_ov020_0207fb04(void);
extern int func_ov020_0207fb14(void);
extern int func_ov020_0207fb8c(void);

asm void *func_ov020_0207fc68(int r0, int *r1)
{
    push    {r3, r4, r5, lr}
    add     r2, r0, #0
    mov     r0, #0x68
    add     r5, r1, #0
    add     r1, r0, #0
    add     r1, #0xf4
    bl      func_ov002_020769b0
    add     r4, r0, #0
    mov     r1, #0
    add     r0, #0x58
    strb    r1, [r0]
    ldr     r1, [r5, #0]
    cmp     r1, #0
    beq     _zero
    add     r0, r4, #0
    add     r0, #0x58
    mov     r2, #0x10
    bl      strncpy
_zero:
    mov     r1, #0
    str     r1, [r4, #0]
    str     r1, [r4, #4]
    str     r1, [r4, #8]
    str     r1, [r4, #0xc]
    ldr     r0, =func_ov020_0207fb04
    str     r1, [r4, #0x10]
    str     r0, [r4, #0x14]
    ldr     r0, =func_ov020_0207fb14
    str     r0, [r4, #0x18]
    str     r1, [r4, #0x1c]
    str     r1, [r4, #0x20]
    str     r1, [r4, #0x24]
    str     r1, [r4, #0x2c]
    str     r1, [r4, #0x30]
    str     r1, [r4, #0x34]
    str     r1, [r4, #0x38]
    str     r1, [r4, #0x40]
    str     r1, [r4, #0x44]
    ldr     r0, =func_ov020_0207fb8c
    mov     r1, #6
    str     r0, [r4, #0x3c]
    add     r0, r4, #0
    add     r0, #0x4c
    strh    r1, [r0]
    add     r0, r4, #0
    pop     {r3, r4, r5, pc}
}
