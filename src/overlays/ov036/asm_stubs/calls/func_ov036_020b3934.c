extern void func_ov036_020b39b0(void);
extern void func_ov036_020b3ac4(void);
extern void data_ov036_020b4f40(void);

asm void func_ov036_020b3934(void)
{
    dcd     0xe92d4070
    dcd     0xe59f304c
    dcd     0xe1a04000
    dcd     0xe5930000
    dcd     0xe59436bc
    dcd     0xe2800f65
    dcd     0xe1a06001
    dcd     0xe1a05002
    dcd     0xe353002f
    dcd     0xe2801b0b
    dcd     0x1a000005
    dcd     0xe59407b0
    dcd     0xe3500000
    dcd     0x13500903
    dcd     0x1a000001
    dcd     0xe2810014
    bl      func_ov036_020b39b0
    dcd     0xe1a00004
    dcd     0xe1a02005
    dcd     0xe2861014
    bl      func_ov036_020b3ac4
    dcd     0xe8bd8070
    dcd     data_ov036_020b4f40
}
