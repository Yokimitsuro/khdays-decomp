extern void func_02023930(void);
extern void *data_ov085_020b91d4;

asm void func_ov085_020b90d4(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov085_020b91d4
    bx      ip
}
