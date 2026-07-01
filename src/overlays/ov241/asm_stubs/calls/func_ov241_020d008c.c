extern void func_ov107_020c9ec8(void);
extern void func_ov107_020c6980(void);

asm void func_ov241_020d008c(void *r0, void *r1)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r0, [r5, #0x39c]
    mov     r4, r1
    bl      func_ov107_020c9ec8
    mov     r0, r5
    mov     r1, r4
    bl      func_ov107_020c6980
    ldr     r0, [r5, #0x398]
    add     lr, r5, #0xa0
    add     ip, r0, #0x10
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    ldmia   lr, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    ldmfd   sp!, {r3, r4, r5, pc}
}
