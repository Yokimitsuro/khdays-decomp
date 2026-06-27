extern void func_02023930(void);
extern void data_ov050_020b74c0(void);

asm void func_ov050_020b742c(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov050_020b74c0
    bx      ip
}
