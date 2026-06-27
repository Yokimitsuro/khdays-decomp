extern void func_02023930(void);
extern void *data_ov071_020b99e0;

asm void func_ov071_020b9970(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov071_020b99e0
    bx      ip
}
