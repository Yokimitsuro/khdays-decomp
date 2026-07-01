extern void func_0200d4ec(void);
extern int data_020463e4;

asm void func_0200d5c0(void)
{
    ldr ip, =func_0200d4ec
    mov r1, r0
    ldr r0, =data_020463e4
    bx ip
}
