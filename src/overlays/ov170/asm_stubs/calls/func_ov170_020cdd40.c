extern void func_ov107_020c2f7c(void);
extern void func_ov170_020cdd58(void);

asm void func_ov170_020cdd40(void)
{
    ldr ip, [pc, #8]
    ldr r1, [pc, #8]
    dcd     0xe3a0001b
    bx  ip
    dcd     func_ov107_020c2f7c
    dcd     func_ov170_020cdd58
}
