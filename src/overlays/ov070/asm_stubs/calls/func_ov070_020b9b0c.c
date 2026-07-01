extern void func_02023930(void);
extern void data_ov070_020b9ba0(void);

asm void func_ov070_020b9b0c(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov070_020b9ba0
    bx      ip
}
