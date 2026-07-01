extern void func_02023930(void);
extern void *data_ov033_020b4b00;

asm void func_ov033_020b4a90(void)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov033_020b4b00
    bx      ip
}
