extern void func_02023930(void);
extern int data_ov041_020b4c60;

asm void func_ov041_020b4bf4(void)
{
    ldr ip, =func_02023930
    mov r1, r0
    ldr r0, =data_ov041_020b4c60
    bx ip
}
