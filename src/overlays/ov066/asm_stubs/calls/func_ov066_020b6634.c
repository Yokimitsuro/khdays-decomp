extern char data_ov066_020b6b80[];
extern void func_02030788(void);
extern void func_ov022_020a35f4(void);

asm void func_ov066_020b6634(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r4, r5, r6, lr}
    ldr     r2, [pc, #0x8c]
    mov     r6, r0
    ldr     r0, [r2]
    mov     r5, r1
    add     r0, r0, #0xc50
    add     r4, r0, #0x2000
    bl      func_02030788
    cmp     r0, #0
    bne     _L0044
    add     r0, r6, #0x64
    ldr     r2, [r6, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r6, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L0044:
    bl      func_02030788
    cmp     r0, #0
    bne     _L006c
    add     r0, r6, #0x6c
    ldr     r2, [r6, #0x46c]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r6, #0x46c]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L006c:
    str     r5, [r4]
    mov     r0, #1
    str     r0, [r4, #4]
    mov     r2, #0
    str     r2, [r4, #0x120]
    str     r2, [r4, #8]
    mov     r0, r6
    mov     r1, #0x21
    str     r2, [r4, #0x124]
    bl      func_ov022_020a35f4
    ldmfd   sp!, {r4, r5, r6, pc}
    dcd     data_ov066_020b6b80
}
