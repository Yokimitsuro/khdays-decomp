extern void func_ov302_020cc388(void);
extern void func_ov302_020cc118(void);

asm void func_ov302_020cc410(void)
{
    ldr     ip, =func_ov302_020cc388
    ldr     r3, =func_ov302_020cc118
    bx      ip
}
