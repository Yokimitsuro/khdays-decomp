extern void func_02023930(void);
extern void *data_ov051_020b7300;

asm void func_ov051_020b7290(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov051_020b7300
    bx      ip
}
