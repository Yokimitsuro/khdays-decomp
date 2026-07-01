extern void WM_EndKeySharing_0x020b15a4(void);
extern char data_ov102_020bb920[];

asm void func_ov102_020bb0e0(void *self)
{
    stmdb   sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    ldr     r1, =data_ov102_020bb920
    add     r4, r0, #0x2000
    ldr     r0, [r1]
    mov     r6, #0
    add     r0, r0, #0x178
    ldr     r5, [r4, #0x644]
    mov     r8, r6
    add     r9, r0, #0x2c00
_loop:
    ldr     r2, [r5, #0xc]
    ldr     r0, [r4, #0x63c]
    mov     r1, r9
    add     r7, r2, r8
    bl      WM_EndKeySharing_0x020b15a4
    add     r6, r6, #1
    str     r9, [r7, #0x130]
    cmp     r6, #0xa
    add     r8, r8, #0x1c8
    add     r9, r9, #0x24
    blt     _loop
    ldmia   sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
