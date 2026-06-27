extern void func_02023930(void);
extern void *data_ov042_020b4740;

asm void func_ov042_020b4678(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov042_020b4740
    bx      ip
}
