extern void func_02023930(void);
extern void data_ov088_020bc260(void);

asm void func_ov088_020bc1cc(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov088_020bc260
    bx      ip
}
