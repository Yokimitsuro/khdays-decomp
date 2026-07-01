extern void func_02023930(void);
extern void *data_ov061_020b6f40;

asm void func_ov061_020b6e78(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov061_020b6f40
    bx      ip
}
