extern void func_0200d4d8(void);
extern int data_020463d8;

asm void func_0200d5a8(void)
{
    ldr ip, =func_0200d4d8
    mov r1, r0
    ldr r0, =data_020463d8
    bx ip
}
