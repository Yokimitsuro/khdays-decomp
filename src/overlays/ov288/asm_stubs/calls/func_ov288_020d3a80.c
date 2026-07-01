extern void func_ov107_020c6980(void *r0);
extern void func_ov002_02076ce8(void *r0, void *r1);

asm void func_ov288_020d3a80(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    bl      func_ov107_020c6980
    ldr     r0, [r4, #0x388]
    add     lr, r4, #0xa0
    ldr     ip, [r0]
    ldmia   lr!, {r0, r1, r2, r3}
    add     ip, ip, #0x10
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    ldr     r0, [r4, #0x390]
    cmp     r0, #0
    ldmeqfd sp!, {r4, pc}
    add     r1, r4, #0xb0
    bl      func_ov002_02076ce8
    ldmfd   sp!, {r4, pc}
}
