extern void func_0202fa20(void);

asm void func_ov012_0205bb84(void)
{
    dcd     0xe3a01000
    dcd     0xe580106c
    ldr ip, [pc, #12]
    dcd     0xe580105c
    dcd     0xe3a02001
    dcd     0xe5802050
    bx  ip
    dcd     func_0202fa20
}
