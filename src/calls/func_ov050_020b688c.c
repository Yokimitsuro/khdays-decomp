extern void WM_EndKeySharing_0x020b15a4(void);

asm void func_ov050_020b688c(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    mov     r11, r0
    add     r0, r11, #0x2c
    add     r4, r11, #0x2000
    add     r6, r0, #0x2c00
    mov     r7, #0
    ldr     r5, [r4, #0x644]
    mov     r9, r7
    add     r10, r6, #0x2a8
_loop1:
    ldr     r2, [r5, #0x6c]
    ldr     r0, [r4, #0x63c]
    mov     r1, r10
    add     r8, r2, r9
    bl      WM_EndKeySharing_0x020b15a4
    add     r7, r7, #1
    str     r10, [r8, #0x130]
    cmp     r7, #3
    add     r9, r9, #0x1c8
    add     r10, r10, #0x24
    blt     _loop1
    add     r7, r11, #0x2000
    mov     r5, #0
    ldr     r4, [r7, #0x644]
    mov     r8, r5
    add     r9, r6, #0x23c
_loop2:
    ldr     r2, [r4, #0xc]
    ldr     r0, [r7, #0x640]
    mov     r1, r9
    add     r6, r2, r8
    bl      WM_EndKeySharing_0x020b15a4
    add     r5, r5, #1
    str     r9, [r6, #0x130]
    cmp     r5, #3
    add     r8, r8, #0x1c8
    add     r9, r9, #0x24
    blt     _loop2
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
