extern void func_02030788(void);
extern void func_020315c0(void);
extern void data_ov069_020ba9b8(void);

asm void func_ov069_020b88c0(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe3a0400a
    bl      func_02030788
    bl      func_020315c0
    dcd     0xe3500000
    dcd     0x15902004
    dcd     0x159f1014
    dcd     0x17914102
    dcd     0xe3550000
    dcd     0x15900004
    dcd     0x15850000
    dcd     0xe1a00004
    dcd     0xe8bd8038
    dcd     data_ov069_020ba9b8
}
