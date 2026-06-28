extern void func_02023930(void);
extern int data_ov097_020bc200;

asm void func_ov097_020bc194(void)
{
    ldr ip, =func_02023930
    mov r1, r0
    ldr r0, =data_ov097_020bc200
    bx ip
}
