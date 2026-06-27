extern void func_02023930(void);
extern void data_ov100_020bc120(void);

asm void func_ov100_020bc004(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov100_020bc120
    bx      ip
}
