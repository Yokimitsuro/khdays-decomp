extern void func_ov302_020cc388(void);
extern void func_ov302_020cc364(void);

asm void func_ov302_020cc524(void)
{
    ldr     ip, =func_ov302_020cc388
    ldr     r3, =func_ov302_020cc364
    bx      ip
}
