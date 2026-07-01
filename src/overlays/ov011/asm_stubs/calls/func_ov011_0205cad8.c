extern void func_ov011_0205c884(void);
extern void func_ov011_0205c6fc(void);
extern void data_ov011_0205e960(void);

asm void func_ov011_0205cad8(void)
{
    dcd     0xe92d4008
    dcd     0xe59f0030
    dcd     0xe5900004
    dcd     0xe2800801
    dcd     0xe5d00945
    dcd     0xe3500003
    dcd     0x13500004
    dcd     0x1a000001
    bl      func_ov011_0205c884
    dcd     0xe8bd8008
    dcd     0xe3a00000
    bl      func_ov011_0205c6fc
    dcd     0xe3a00001
    bl      func_ov011_0205c6fc
    dcd     0xe8bd8008
    dcd     data_ov011_0205e960
}
