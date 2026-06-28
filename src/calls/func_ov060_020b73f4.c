extern void func_02023930(void);
extern int data_ov060_020b7460;

asm void func_ov060_020b73f4(void)
{
    ldr ip, =func_02023930
    mov r1, r0
    ldr r0, =data_ov060_020b7460
    bx ip
}
