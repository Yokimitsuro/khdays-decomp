extern void func_0200d538(void);
extern int data_020463e4;

asm void func_0200d5f0(void)
{
    ldr ip, =func_0200d538
    mov r1, r0
    ldr r0, =data_020463e4
    bx ip
}
