extern void *data_ov030_020b5a00;
extern void func_ov030_020b4cd4(void);

asm void func_ov030_020b3e44(void)
{
    ldr     r0, =data_ov030_020b5a00
    ldr     ip, =func_ov030_020b4cd4
    ldr     r0, [r0, #0]
    add     r0, r0, #0xcb0
    add     r0, r0, #0x2000
    bx      ip
}
