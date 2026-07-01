extern void func_02034014(void);
extern void data_ov011_0205e960(void);
extern void func_ov011_0205cb18(void);

asm void func_ov011_0205ae14(void)
{
    dcd     0xe92d4008
    mov r0, #0
    bl      func_02034014
    dcd     0xe3500000
    dcd     0x13a00000
    dcd     0x18bd8008
    dcd     0xe59f0010
    dcd     0xe3a02005
    dcd     0xe5901004
    dcd     0xe59f0008
    dcd     0xe5812004
    dcd     0xe8bd8008
    dcd     data_ov011_0205e960
    dcd     func_ov011_0205cb18
}
