extern void func_ov302_020cc388(void);
extern void func_ov302_020cc33c(void);

asm void func_ov302_020cc4fc(void)
{
    ldr     ip, =func_ov302_020cc388
    ldr     r3, =func_ov302_020cc33c
    bx      ip
}
