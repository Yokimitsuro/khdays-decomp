extern void *data_ov053_020b7e60;

asm void func_ov053_020b7924(void)
{
    ldr     r1, =data_ov053_020b7e60
    add     r0, r0, #0x2f8
    ldr     r1, [r1]
    mov     r2, #0
    add     r1, r1, #0xe4
    add     r1, r1, #0x2c00
    str     r2, [r1, #0x10]
    add     r2, r0, #0x2000
    ldr     r0, [r2, #0x348]
    add     r0, r0, #4
    str     r0, [r1, #0x130]
    ldr     r0, [r2, #0x344]
    add     r0, r0, #4
    str     r0, [r1, #0x134]
    bx      lr
}
