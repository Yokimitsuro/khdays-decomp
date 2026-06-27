extern void func_0202a634(void *r0, void *r1, int r2, int r3);
extern void func_ov098_020bb3c0(void *r0);
extern char data_ov098_020bbda0[];
extern char data_ov098_020bbd54[];

asm void func_ov098_020bb2d4(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    ldr     r0, [pc, #0x70]
    mov     r2, #0
    ldr     r4, [r0]
    mov     r5, r2
    add     r0, r4, #0x2c
    add     r1, r0, #0x2c00
    add     r0, r4, #0x2000
    mov     r3, r1
    str     r2, [r0, #0xc2c]
_L_loop1:
    add     r2, r2, #1
    str     r5, [r3, #0x14]
    cmp     r2, #7
    add     r3, r3, #0x10c
    blt     _L_loop1
    ldr     r7, [pc, #0x3c]
    add     r8, r1, #0x18
    mov     r6, #1
_L_loop2:
    ldrb    r3, [r4, #9]
    mov     r0, r8
    mov     r1, r7
    mov     r2, r6
    add     r3, r3, #7
    bl      func_0202a634
    add     r5, r5, #1
    cmp     r5, #7
    add     r8, r8, #0x10c
    blt     _L_loop2
    mov     r0, r4
    bl      func_ov098_020bb3c0
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
    dcd     data_ov098_020bbda0
    dcd     data_ov098_020bbd54
}
