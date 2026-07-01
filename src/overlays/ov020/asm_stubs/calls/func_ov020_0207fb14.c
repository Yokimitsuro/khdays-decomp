extern int func_ov002_0206da70(void *p);
extern void func_0202a634(void *r0, int r1, int r2, int r3);
extern void func_ov002_0207c618(void *r0, int r1, int r2);
extern void func_0202af2c(void *r0);

asm void func_ov020_0207fb14(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r1, [r4, #8]
    ldrsb   r0, [r1, #0x58]
    cmp     r0, #0
    ldmeqfd sp!, {r4, pc}
    add     r0, r1, #0x58
    bl      func_ov002_0206da70
    mov     r1, r0
    add     r0, r4, #0x1c
    mov     r2, #1
    mov     r3, #4
    bl      func_0202a634
    add     r3, r4, #0xc0
    ldmia   r3, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, #0x6000
    str     r0, [r4, #0xd4]
    str     r0, [r4, #0xd0]
    str     r0, [r4, #0xcc]
    ldrh    r3, [r4, #0x12]
    mov     r1, #0
    mov     r2, r1
    orr     r3, r3, #4
    add     r0, r4, #0x1c
    strh    r3, [r4, #0x12]
    bl      func_ov002_0207c618
    add     r0, r4, #0x1c
    bl      func_0202af2c
    ldmfd   sp!, {r4, pc}
}
