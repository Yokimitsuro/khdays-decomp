extern void func_ov022_020b15b0(int r0, int r1);
extern void *func_ov022_020b14a4(void *r0, int r1, int r2, void *r3);
extern void func_ov022_020b1cec(void *r0, int r1);
extern char data_ov042_020b4790[];
extern char data_ov042_020b47a0[];

asm void func_ov042_020b3788(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    add     r0, r5, #0x2f8
    add     r4, r0, #0x2000
    mov     r0, #0
    strb    r0, [r4, #0x334]
    ldrb    r0, [r5, #9]
    mov     r1, #2
    bl      func_ov022_020b15b0
    ldr     r2, [r5, #0x20]
    ldrb    r1, [r5, #9]
    add     r3, r2, #4
    ldr     r0, [pc, #0x48]
    mov     r2, #0
    bl      func_ov022_020b14a4
    str     r0, [r4, #0x340]
    add     r0, r5, #0x2000
    ldr     r0, [r0, #0x644]
    ldrb    r1, [r5, #9]
    ldr     r2, [r0, #0xc]
    ldr     r0, [pc, #0x2c]
    add     r3, r2, #0x28
    mov     r2, #1
    bl      func_ov022_020b14a4
    str     r0, [r4, #0x344]
    add     r0, r5, #0xda0
    mov     r1, #0xc7
    bl      func_ov022_020b1cec
    ldrb    r0, [r4, #0x334]
    orr     r0, r0, #0xb
    strb    r0, [r4, #0x334]
    ldmfd   sp!, {r3, r4, r5, pc}
    dcd     data_ov042_020b4790
    dcd     data_ov042_020b47a0
}
