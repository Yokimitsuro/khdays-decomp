extern void func_02023930(void);
extern void *data_ov034_020b55c0;

asm void func_ov034_020b5558(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov034_020b55c0
    bx      ip
}
