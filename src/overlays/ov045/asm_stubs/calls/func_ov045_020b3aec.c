extern void func_0202afdc(void);
extern void func_ov045_020b4254(void);
extern void func_ov045_020b4450(void);
extern void *data_ov045_020b4c20;

asm void func_ov045_020b3aec(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r1, =data_ov045_020b4c20
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
    bl      func_ov045_020b4254
    mov     r0, r5
    add     r1, r4, #0x2000
    bl      func_ov045_020b4450
    ldmfd   sp!, {r3, r4, r5, pc}
}
