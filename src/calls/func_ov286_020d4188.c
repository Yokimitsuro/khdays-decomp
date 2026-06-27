extern void func_ov107_020cab14(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_02023eb4(void);
extern void func_ov286_020d4210(void);

asm void func_ov286_020d4188(void *arg)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #0
    ldr     r0, [r4]
    bl      func_ov107_020cab14
    str     r0, [r4, #0x18]
    cmp     r0, #0
    bne     _ok
    ldr     r0, [r4]
    mov     r1, #2
    strb    r1, [r0, #0x1c7]
    ldrsb   r1, [r5, #0x20]
    mov     r0, r5
    mov     r2, #0
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
_ok:
    mov     r0, #0
    str     r0, [r4, #0x28]
    mov     r1, #1
    ldr     r0, [r4]
    mov     r2, r1
    bl      func_ov107_020c9264
    ldr     r0, =0x00003001
    bl      func_02023eb4
    add     r0, r0, #0x1000
    str     r0, [r4, #0x2c]
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov286_020d4210
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
