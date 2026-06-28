extern void func_02023930(void);
extern int data_ov032_020b57f4;

asm void func_ov032_020b56d0(void)
{
    ldr ip, =func_02023930
    mov r1, r0
    ldr r0, =data_ov032_020b57f4
    bx ip
}
