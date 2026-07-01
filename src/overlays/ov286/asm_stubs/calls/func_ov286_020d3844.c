extern void func_01fffca8(void);
extern void func_0203b898(void);
extern void func_0203bfb4(void);
extern void func_ov107_020c319c(void);
extern void func_ov107_020c92b0(void);
extern void func_ov107_020c9440(void);
extern void func_ov286_020d3984(void);
extern void func_ov286_020d39a0(void);
extern void func_ov286_020d39fc(void);
extern void func_ov286_020d3a1c(void);
extern void func_ov286_020d3a68(void);
extern void func_ov286_020d3adc(void);

asm void func_ov286_020d3844(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r2, =func_ov286_020d3984
    mov     r4, r0
    ldr     r1, =func_ov286_020d39a0
    str     r2, [r4, #8]
    ldr     r2, =func_ov286_020d3a1c
    str     r1, [r4, #0xc]
    ldr     r1, =func_ov286_020d3a68
    str     r2, [r4, #0x30]
    ldr     r2, =func_ov286_020d3adc
    str     r1, [r4, #0x1d0]
    ldr     r1, =func_ov286_020d39fc
    str     r2, [r4, #0x1e0]
    str     r1, [r4, #0x1dc]
    mov     r2, #0xc00
    str     r2, [r4, #0x70]
    mov     r1, #0
    str     r1, [r4, #0x64]
    str     r2, [r4, #0x68]
    str     r1, [r4, #0x6c]
    bl      func_ov107_020c9440
    bl      func_0203b898
    str     r0, [r4, #0x384]
    ldr     r0, [r4, #0x9c]
    ldr     r1, [r4, #0x384]
    bl      func_0203bfb4
    ldr     r0, =0x00001f33
    mov     r1, #0
    str     r0, [sp]
    mov     r0, r4
    mov     r2, #1
    mov     r3, r1
    bl      func_ov107_020c92b0
    ldr     r1, =0x00001f33
    mov     r0, r4
    str     r1, [sp]
    mov     r1, #1
    mov     r2, r1
    mov     r3, #0
    bl      func_ov107_020c92b0
    ldr     r1, =0x00001f33
    mov     r0, r4
    str     r1, [sp]
    mov     r1, #2
    mov     r2, #1
    mov     r3, #0
    bl      func_ov107_020c92b0
    ldr     r1, =0x00001f33
    mov     r0, r4
    str     r1, [sp]
    mov     r1, #4
    mov     r2, #1
    mov     r3, #0
    bl      func_ov107_020c92b0
    add     r0, r4, #0x22c
    mov     r1, #0x10
    mov     r2, #0x64
    bl      func_01fffca8
    str     r0, [r4, #0x38c]
    add     r0, r4, #0x64
    bl      func_ov107_020c319c
    ldr     r2, [r4, #0x38c]
    mov     r1, #4
    str     r0, [r2]
    add     r0, r4, #0x144
    mov     r2, #0x64
    bl      func_01fffca8
    mov     r5, r0
    add     r0, r4, #0x64
    bl      func_ov107_020c319c
    str     r0, [r5]
    str     r0, [r4, #0x388]
    ldmfd   sp!, {r3, r4, r5, pc}
}
