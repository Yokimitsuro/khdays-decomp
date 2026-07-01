extern void func_ov107_020c2f7c(void);
extern void func_ov251_020d37b8(void);

asm void func_ov251_020d37a0(void)
{
    ldr ip, [pc, #8]
    ldr r1, [pc, #8]
    dcd     0xe3a0004b
    bx  ip
    dcd     func_ov107_020c2f7c
    dcd     func_ov251_020d37b8
}
