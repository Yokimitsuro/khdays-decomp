extern int func_ov302_020cc410(int);
extern int func_ov302_020cc424(int);
extern int func_ov302_020cc4d4(int);
extern int func_ov302_020cc4c0(int);
extern int func_ov302_020cc4e8(int);
extern int func_ov302_020cc4fc(int);
extern int func_ov302_020cc510(int);
extern int func_ov302_020cc524(int);

asm void func_ov302_020cc598(void *r0, int r1)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    cmp     r1, #7
    addls   pc, pc, r1, lsl #2
    ldmfd   sp!, {r4, pc}
    b       _c0
    b       _c1
    b       _c2
    b       _c3
    b       _c4
    b       _c5
    b       _c6
    b       _c7
_c0:
    ldr     r1, [r4, #0x14]
    bl      func_ov302_020cc410
    strh    r0, [r4, #0x10]
    ldmfd   sp!, {r4, pc}
_c1:
    ldr     r1, [r4, #0x14]
    bl      func_ov302_020cc424
    strh    r0, [r4, #0x10]
    ldmfd   sp!, {r4, pc}
_c2:
    ldr     r1, [r4, #0x14]
    bl      func_ov302_020cc4d4
    strh    r0, [r4, #0x10]
    ldmfd   sp!, {r4, pc}
_c3:
    ldr     r1, [r4, #0x14]
    bl      func_ov302_020cc4c0
    strh    r0, [r4, #0x10]
    ldmfd   sp!, {r4, pc}
_c4:
    ldr     r1, [r4, #0x14]
    bl      func_ov302_020cc4e8
    strh    r0, [r4, #0x10]
    ldmfd   sp!, {r4, pc}
_c5:
    ldr     r1, [r4, #0x14]
    bl      func_ov302_020cc4fc
    strh    r0, [r4, #0x10]
    ldmfd   sp!, {r4, pc}
_c6:
    ldr     r1, [r4, #0x14]
    bl      func_ov302_020cc510
    strh    r0, [r4, #0x10]
    ldmfd   sp!, {r4, pc}
_c7:
    ldr     r1, [r4, #0x14]
    bl      func_ov302_020cc524
    strh    r0, [r4, #0x10]
    ldmfd   sp!, {r4, pc}
}
