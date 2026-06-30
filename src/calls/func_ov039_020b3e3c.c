extern void func_0202a7dc(void);
extern void func_ov039_020b445c(void);
extern void data_ov039_020b5600(void);

asm void func_ov039_020b3e3c(void)
{
    dcd     0xe92d4070
    dcd     0xe59f1034
    dcd     0xe1a06000
    dcd     0xe5910000
    dcd     0xe3a04000
    dcd     0xe2800ecf
    dcd     0xe2805a02
    dcd     0xe1a00005
    bl      func_0202a7dc
    dcd     0xe2844001
    dcd     0xe3540002
    dcd     0xe2855f43
    dcd     0xbafffff9
    dcd     0xe1a00006
    bl      func_ov039_020b445c
    dcd     0xe8bd8070
    dcd     data_ov039_020b5600
}
