extern void func_02023930(void);
extern void data_ov031_020b4cc0(void);

asm void func_ov031_020b4c2c(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov031_020b4cc0
    bx      ip
}
