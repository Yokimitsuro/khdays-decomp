extern void func_ov107_020c9264(void);
extern void func_0203cd7c(void);
extern void func_0202ea48(void);
extern void func_0203c634(void);
extern int data_02042264;
extern void func_ov117_020ccfb4(void);

asm void func_ov117_020ccf38(void *r0)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0x24
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #2
    ldr     r0, [r4]
    mov     r2, #0
    bl      func_ov107_020c9264
    ldr     r1, [r4, #0x4c]
    cmp     r1, #0
    beq     _L5c
    ldr     r2, [r4, #0x44]
    ldr     r3, =data_02042264
    add     r0, sp, #0
    add     r1, r1, #0x190
    bl      func_0203cd7c
    add     r1, sp, #0
    add     r0, r4, #0x18
    bl      func_0202ea48
    add     r0, r4, #0x18
    add     ip, r4, #8
    ldmia   r0, {r0, r1, r2, r3}
    stmia   ip, {r0, r1, r2, r3}
_L5c:
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov117_020ccfb4
    mov     r0, r5
    bl      func_0203c634
    add     sp, sp, #0x24
    ldmfd   sp!, {r4, r5, pc}
}
