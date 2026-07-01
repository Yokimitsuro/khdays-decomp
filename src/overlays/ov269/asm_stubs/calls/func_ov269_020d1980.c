extern void func_ov107_020c2f7c(void);
extern void func_ov269_020d1998(void);

asm void func_ov269_020d1980(void)
{
    ldr ip, [pc, #8]
    ldr r1, [pc, #8]
    dcd     0xe3a0005c
    bx  ip
    dcd     func_ov107_020c2f7c
    dcd     func_ov269_020d1998
}
