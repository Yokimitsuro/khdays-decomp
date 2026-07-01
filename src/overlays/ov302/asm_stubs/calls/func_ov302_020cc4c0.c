extern void func_ov302_020cc388(void);
extern void func_ov302_020cc168(void);

asm void func_ov302_020cc4c0(void)
{
    ldr     ip, =func_ov302_020cc388
    ldr     r3, =func_ov302_020cc168
    bx      ip
}
