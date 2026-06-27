extern void func_0202afdc(void);
extern void func_ov100_020bb7f4(void);
extern void func_ov100_020bb9f0(void);
extern void data_ov100_020bc1c0(void);

asm void func_ov100_020bb08c(void)
{
    stmdb   sp!, {r3, r4, r5, lr}
    ldr     r1, =data_ov100_020bc1c0
    mov     r5, r0
    ldr     r2, [r1]
    add     r1, r5, #0xe00
    add     r0, r2, #0xc30
    ldrh    r1, [r1, #0xb0]
    add     r0, r0, #0x2000
    add     r4, r2, #0xdf0
    bl      func_0202afdc
    add     r0, r5, #0x2a00
    ldrsh   r2, [r0, #0xba]
    mov     r0, r5
    add     r1, r4, #0x2000
    bl      func_ov100_020bb7f4
    mov     r0, r5
    add     r1, r4, #0x2000
    bl      func_ov100_020bb9f0
    ldmia   sp!, {r3, r4, r5, pc}
}
