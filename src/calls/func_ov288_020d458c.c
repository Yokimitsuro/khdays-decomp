extern void func_ov107_020c9264(void *r0, int r1, int r2);
extern void func_0203c634(void *r0, int r1, void *r2);
extern int data_02041dc8;
extern void func_ov288_020d45fc(void);

asm void func_ov288_020d458c(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #1
    ldr     r0, [r4]
    mov     r2, #0
    bl      func_ov107_020c9264
    ldr     r0, [r4]
    mov     r1, #1
    str     r1, [r0, #0x394]
    ldr     r0, [r4, #0xc]
    add     r3, r4, #0x10
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, =data_02041dc8
    add     r3, r4, #0x1c
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, #0
    str     r0, [r4, #8]
    str     r0, [r4, #0x58]
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov288_020d45fc
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
