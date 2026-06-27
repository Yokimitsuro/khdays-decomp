extern void func_ov302_020cc388(void);
extern void func_ov302_020cc2bc(void);

asm void func_ov302_020cc4e8(void)
{
    ldr     ip, =func_ov302_020cc388
    ldr     r3, =func_ov302_020cc2bc
    bx      ip
}
