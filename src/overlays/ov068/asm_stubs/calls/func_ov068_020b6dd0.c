extern void func_ov022_020a35f4(void);
extern void *data_ov068_020b7500;

asm void func_ov068_020b6dd0(void)
{
    ldr     r2, =data_ov068_020b7500
    ldr     ip, =func_ov022_020a35f4
    ldr     r2, [r2]
    mov     r3, #0
    add     r2, r2, #0xfc
    add     r2, r2, #0x2c00
    str     r1, [r2, #0x118]
    mov     r1, #0x22
    str     r3, [r2, #0x11c]
    bx      ip
}
