extern void OS_SPrintf(void);
extern void data_ov172_020d2b00(void);
extern void func_0203d15c(void);
extern void func_ov107_020c6624(void);
extern void func_ov107_020c9c24(void);
extern void func_ov172_020cfc60(void);

asm void func_ov172_020cfb78(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd020
    dcd     0xe1a05000
    dcd     0xe28d2000
    dcd     0xe3a00007
    dcd     0xe3a01000
    dcd     0xe5c21000
    dcd     0xe5c21001
    dcd     0xe5c21002
    dcd     0xe5c21003
    dcd     0xe2822004
    dcd     0xe2500001
    dcd     0x1afffff8
    dcd     0xe3a00e3b
    dcd     0xe5c21000
    bl      func_0203d15c
    dcd     0xe1a04000
    dcd     0xe3a0201c
    dcd     0xe59f1034
    dcd     0xe28d0000
    dcd     0xe5c4219c
    bl      OS_SPrintf
    dcd     0xe28d0000
    bl      func_ov107_020c9c24
    dcd     0xe58401a4
    dcd     0xe59f201c
    dcd     0xe1a00004
    dcd     0xe1a01005
    dcd     0xe584218c
    bl      func_ov107_020c6624
    dcd     0xe1a00004
    dcd     0xe28dd020
    dcd     0xe8bd8038
    dcd     data_ov172_020d2b00
    dcd     func_ov172_020cfc60
}
