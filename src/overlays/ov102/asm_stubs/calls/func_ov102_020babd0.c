extern void func_02030788(void);
extern void func_ov022_02083f90(void);
extern void func_ov022_020912d8(void);
extern void func_ov022_0209145c(void);
extern void func_ov022_02091474(void);
extern void func_ov022_020ad588(void);

asm void func_ov102_020babd0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    bl      func_ov022_02083f90
    add     r2, r4, #0x2000
    mov     r1, r0
    ldr     r0, [r2, #0x644]
    bl      func_ov022_0209145c
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      func_ov022_02091474
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      func_ov022_020912d8
    cmp     r0, #0
    bne     _L008c
    bl      func_02030788
    cmp     r0, #0
    bne     _L0064
    add     r0, r4, #0x64
    ldr     r2, [r4, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r4, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L0064:
    bl      func_02030788
    cmp     r0, #0
    bne     _L008c
    add     r0, r4, #0x6c
    ldr     r2, [r4, #0x46c]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r4, #0x46c]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L008c:
    mov     r0, r4
    bl      func_ov022_020ad588
    ldmfd   sp!, {r4, pc}
}
