extern void func_ov039_020b3f54(void);
extern void func_ov039_020b4168(void);

asm void func_ov039_020b3e8c(void)
{
    dcd     0xe92d41f0
    dcd     0xe1a07001
    dcd     0xe1a08000
    dcd     0xe1a06002
    dcd     0xe2875018
    dcd     0xe3a04000
    dcd     0xe1a00008
    dcd     0xe1a01005
    dcd     0xe1a02006
    bl      func_ov039_020b3f54
    dcd     0xe2844001
    dcd     0xe3540002
    dcd     0xe2855f43
    dcd     0xbafffff7
    dcd     0xe1a00008
    dcd     0xe1a02006
    dcd     0xe2871fc2
    bl      func_ov039_020b4168
    dcd     0xe8bd81f0
}
