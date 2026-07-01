extern int func_ov022_020894f8(int a, int b);
extern int func_ov022_020ad44c(int a, int b);
extern void VEC_MultAdd(int a, int b, int c, int d, int e);
extern int func_ov022_020893f4(int a, int b, int c);
extern int func_ov022_0208963c(int a);
extern void MTX_Identity33_(int a);
extern void MTX_RotY33_(int a, int b, int c);
extern void MTX_Concat33(int a, int b, int c);
extern void MTX_RotX33_(int a, int b, int c);

asm void func_ov013_0207fd2c(void *r0, void *r1)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0x84
    mov     r5, r0
    mov     r4, r1
    ldr     r0, [r5, #0x7c8]
    ldr     r1, [r5, #0x7cc]
    bl      func_ov022_020894f8
    cmp     r0, #0
    mvnne   r0, #0
    strne   r0, [r5, #0x7cc]
    ldr     r1, [r5, #0x7cc]
    mvn     r0, #0
    cmp     r1, r0
    addne   sp, sp, #0x84
    ldmnefd sp!, {r4, r5, pc}
    add     r0, r5, #0x250
    add     r3, sp, #0x78
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    add     r0, sp, #0x6c
    mov     r1, r5
    bl      func_ov022_020ad44c
    ldr     r12, [sp, #0x70]
    add     r2, sp, #0x78
    mov     r0, #0x800
    mov     r1, r4
    mov     r3, r2
    str     r12, [sp, #0x7c]
    rsb     r0, r0, #0
    bl      VEC_MultAdd
    ldr     r0, [r5, #0x7c8]
    add     r1, sp, #0x78
    mov     r2, #0
    bl      func_ov022_020893f4
    cmp     r0, #0
    addlt   sp, sp, #0x84
    ldmltfd sp!, {r4, r5, pc}
    str     r0, [r5, #0x7cc]
    ldr     r0, [r5, #0x7c8]
    ldr     r1, [r5, #0x7cc]
    bl      func_ov022_0208963c
    mov     r5, r0
    mov     r1, #0x2000
    str     r1, [r5, #0xb8]
    str     r1, [r5, #0xb4]
    add     r0, sp, #0
    str     r1, [r5, #0xb0]
    bl      MTX_Identity33_
    ldr     r1, [r4]
    ldr     r2, [r4, #8]
    add     r0, sp, #0x48
    bl      MTX_RotY33_
    add     r1, sp, #0
    add     r0, sp, #0x48
    mov     r2, r1
    bl      MTX_Concat33
    add     r0, sp, #0x24
    mov     r1, #0x1000
    mov     r2, #0
    bl      MTX_RotX33_
    add     r0, sp, #0x24
    add     r1, sp, #0
    add     r2, r5, #0x80
    bl      MTX_Concat33
    ldrh    r0, [r5]
    bic     r0, r0, #0x20
    strh    r0, [r5]
    add     sp, sp, #0x84
    ldmfd   sp!, {r4, r5, pc}
}
