extern void func_02023930(void);
extern void *data_ov066_020b6af4;

asm void func_ov066_020b69f4(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov066_020b6af4
    bx      ip
}
