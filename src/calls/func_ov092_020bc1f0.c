extern void func_ov022_0209145c(void);
extern void func_ov092_020bc234(void);

asm void func_ov092_020bc1f0(void)
{
    dcd     0xe92d41f0
    dcd     0xe3a05000
    dcd     0xe1a08000
    dcd     0xe1a07001
    dcd     0xe1a06005
    dcd     0xe2884a02
    dcd     0xe5940644
    dcd     0xe1a01007
    dcd     0xe0800006
    bl      func_ov022_0209145c
    dcd     0xe2855001
    dcd     0xe3550003
    dcd     0xe2866030
    dcd     0xbafffff7
    dcd     0xe1a00008
    bl      func_ov092_020bc234
    dcd     0xe8bd81f0
}
