extern void func_02023930(void);
extern char data_ov102_020bb894[];

asm void func_ov102_020bb794(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov102_020bb894
    bx      ip
}
