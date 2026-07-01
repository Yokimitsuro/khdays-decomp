extern void func_0203d040(void);
extern void func_0202f188(void);
extern void func_0202ed60(void);
extern void func_0202ef54(void);
extern void func_0203c9d0(void);
extern void data_02042264(void);

asm void func_ov153_020cd6d0(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd020
    dcd     0xe5904004
    dcd     0xe5940000
    dcd     0xe5d001c4
    dcd     0xe3100002
    dcd     0x1a000005
    dcd     0xe5940010
    dcd     0xe5941014
    dcd     0xe5942020
    dcd     0xe3a03000
    bl      func_0203d040
    dcd     0xe5840010
    dcd     0xe5942010
    dcd     0xe59f1040
    dcd     0xe28d0000
    bl      func_0202f188
    dcd     0xe5942000
    dcd     0xe59f1030
    dcd     0xe28d0010
    dcd     0xe2822f49
    bl      func_0202ed60
    dcd     0xe28d0010
    dcd     0xe28d2000
    dcd     0xe1a01000
    bl      func_0202ef54
    dcd     0xe5940000
    dcd     0xe28d1010
    dcd     0xe28000a0
    bl      func_0203c9d0
    dcd     0xe28dd020
    dcd     0xe8bd8010
    dcd     data_02042264
}
