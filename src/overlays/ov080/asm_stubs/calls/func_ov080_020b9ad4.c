extern void func_02023930(void);
extern int data_ov080_020b9b40;

asm void func_ov080_020b9ad4(void)
{
    ldr ip, =func_02023930
    mov r1, r0
    ldr r0, =data_ov080_020b9b40
    bx ip
}
