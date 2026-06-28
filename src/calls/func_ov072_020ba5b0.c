extern void func_02023930(void);
extern int data_ov072_020ba6d4;

asm void func_ov072_020ba5b0(void)
{
    ldr ip, =func_02023930
    mov r1, r0
    ldr r0, =data_ov072_020ba6d4
    bx ip
}
