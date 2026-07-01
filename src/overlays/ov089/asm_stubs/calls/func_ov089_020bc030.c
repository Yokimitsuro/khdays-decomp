extern void func_02023930(void);
extern void *data_ov089_020bc0a0;

asm void func_ov089_020bc030(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov089_020bc0a0
    bx      ip
}
