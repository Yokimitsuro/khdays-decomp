extern void func_0202a818(void);
extern void func_02030788(void);
extern void func_ov046_020b4504(void);
extern void func_ov046_020b4608(void);

asm void func_ov046_020b445c(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05000
    dcd     0xe5952000
    dcd     0xe1a06001
    dcd     0xe3520001
    dcd     0xe3a04000
    dcd     0x0a000002
    dcd     0xe3520002
    dcd     0x0a000009
    dcd     0xea000013
    dcd     0xe595110c
    dcd     0xe0811006
    dcd     0xe585110c
    dcd     0xe3510a0a
    dcd     0xba00000e
    bl      func_ov046_020b4608
    dcd     0xe3a00002
    dcd     0xe5850000
    dcd     0xea00000a
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000001
    dcd     0xe1a00005
    bl      func_ov046_020b4504
    dcd     0xe1a01006
    dcd     0xe2850004
    bl      func_0202a818
    dcd     0xe3500000
    dcd     0x13a00000
    dcd     0x15850000
    dcd     0xe5950000
    dcd     0xe3500000
    dcd     0x03a04001
    dcd     0xe1a00004
    dcd     0xe8bd8070
}
