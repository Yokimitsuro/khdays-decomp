extern void func_02023930(void);
extern void *data_ov045_020b4b80;

asm void func_ov045_020b4a64(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov045_020b4b80
    bx      ip
}
