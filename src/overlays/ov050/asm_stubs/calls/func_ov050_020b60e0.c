extern void func_0202a634(void);
extern void func_ov050_020b6600(void);
extern void *data_ov050_020b75c0;
extern void *data_ov050_020b755c;

asm void func_ov050_020b60e0(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    ldr     r0, =data_ov050_020b75c0
    mov     r6, #0
    ldr     r9, [r0]
    ldr     r5, =data_ov050_020b755c
    add     r0, r9, #0x2c
    add     r1, r9, #0x2000
    add     r8, r0, #0x2c00
    str     r6, [r1, #0xc2c]
    str     r6, [r8, #4]
    add     r7, r8, #0x14
    mov     r4, #1
    mov     r10, r6
_loop:
    ldrb    r3, [r9, #9]
    mov     r0, r7
    mov     r1, r5
    mov     r2, r4
    add     r3, r3, #7
    bl      func_0202a634
    str     r6, [r8, #0xc]
    add     r6, r6, #1
    str     r10, [r8, #0x10]
    cmp     r6, #2
    add     r7, r7, #0x118
    add     r8, r8, #0x118
    blt     _loop
    mov     r0, r9
    bl      func_ov050_020b6600
    ldmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
}
