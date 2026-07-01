extern void WM_EndKeySharing_0x020b15a4(void *r0, void *r1);
extern char data_ov042_020b4800[];

asm void func_ov042_020b403c(void *r0)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    ldr     r1, [pc, #0x48]
    add     r4, r0, #0x2000
    ldr     r0, [r1]
    mov     r6, #0
    add     r0, r0, #0x394
    ldr     r5, [r4, #0x644]
    mov     r8, r6
    add     r9, r0, #0x3000
_L_loop:
    ldr     r2, [r5, #0xc]
    ldr     r0, [r4, #0x63c]
    mov     r1, r9
    add     r7, r2, r8
    bl      WM_EndKeySharing_0x020b15a4
    add     r6, r6, #1
    str     r9, [r7, #0x130]
    cmp     r6, #6
    add     r8, r8, #0x1c8
    add     r9, r9, #0x24
    blt     _L_loop
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    dcd     data_ov042_020b4800
}
