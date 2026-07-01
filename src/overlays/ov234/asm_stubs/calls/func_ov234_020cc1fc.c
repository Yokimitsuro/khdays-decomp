extern void func_ov107_020c6980(void *);

asm void func_ov234_020cc1fc(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    bl      func_ov107_020c6980
    ldr     r0, [r4, #0x38c]
    add     lr, r4, #0xa0
    add     ip, r0, #0x10
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    ldr     r1, [r4, #0x388]
    ldr     r0, [r4, #0x38c]
    ldr     r1, [r1]
    add     lr, r0, #0x10
    add     ip, r1, #0x10
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    ldmfd   sp!, {r4, pc}
}
