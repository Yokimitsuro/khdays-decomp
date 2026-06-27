extern void func_02023930(void);
extern void *data_ov030_020b58f4;

asm void func_ov030_020b3e84(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov030_020b58f4
    bx      ip
}
