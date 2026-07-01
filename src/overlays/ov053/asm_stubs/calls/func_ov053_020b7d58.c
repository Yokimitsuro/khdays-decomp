extern void func_02023930(void);
extern void *data_ov053_020b7dc0;

asm void func_ov053_020b7d58(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov053_020b7dc0
    bx      ip
}
