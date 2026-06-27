extern void func_ov107_020c6980(void);

asm void func_ov286_020d39a0(void *arg)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    bl      func_ov107_020c6980
    ldr     r0, [r4, #0x38c]
    add     lr, r4, #0xa0
    ldr     ip, [r0]
    ldmia   lr!, {r0, r1, r2, r3}
    add     ip, ip, #0x10
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    ldr     r0, [r4, #0x388]
    add     lr, r4, #0xa0
    add     ip, r0, #0x10
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    ldmfd   sp!, {r4, pc}
}
