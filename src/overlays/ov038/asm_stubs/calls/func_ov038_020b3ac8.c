extern void func_ov022_020a4490(void);
extern void data_ov038_020b4ca0(void);

asm void func_ov038_020b3ac8(void)
{
    dcd     0xe92d4010
    dcd     0xe59f202c
    dcd     0xe3a03000
    dcd     0xe592c000
    dcd     0xe3a02001
    dcd     0xe581310c
    dcd     0xe5812000
    dcd     0xe28c302c
    dcd     0xe3a010c8
    dcd     0xe3a02005
    dcd     0xe2834b0b
    bl      func_ov022_020a4490
    dcd     0xe5840550
    dcd     0xe8bd8010
    dcd     data_ov038_020b4ca0
}
