extern void func_0202a7dc(void);
extern void *data_ov089_020bc120;

asm void func_ov089_020baba8(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r0, =data_ov089_020bc120
    ldr     r0, [r0]
    add     r0, r0, #0x2c
    add     r4, r0, #0x2c00
    add     r0, r4, #0xc
    bl      func_0202a7dc
    add     r5, r4, #0x120
    mov     r4, #0
_loop:
    mov     r0, r5
    bl      func_0202a7dc
    add     r4, r4, #1
    cmp     r4, #6
    add     r5, r5, #0x110
    blt     _loop
    ldmfd   sp!, {r3, r4, r5, pc}
}
