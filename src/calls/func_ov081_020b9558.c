extern void func_02023930(void);
extern void *data_ov081_020b9620;

asm void func_ov081_020b9558(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov081_020b9620
    bx      ip
}
