extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov117_020ccdf4(void);

asm void func_ov117_020ccdc0(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r0, [r4, #4]
    mov     r1, #1
    ldr     r0, [r0]
    mov     r2, r1
    bl      func_ov107_020c9264
    ldrsb   r1, [r4, #0x20]
    ldr     r2, =func_ov117_020ccdf4
    mov     r0, r4
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
