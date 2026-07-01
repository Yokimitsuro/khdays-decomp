extern void func_02023930(void);
extern int data_ov052_020b7ff4;

asm void func_ov052_020b7ed0(void)
{
    ldr ip, =func_02023930
    mov r1, r0
    ldr r0, =data_ov052_020b7ff4
    bx ip
}
