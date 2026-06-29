extern void func_02030788(void);
extern void func_ov002_0204cdf4(void);
extern void func_ov022_02083f0c(void);
extern void func_ov022_020ad588(void);
extern void func_ov022_020ad718(void);

asm void func_ov103_020bab3c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe59516bc
    dcd     0xe285002c
    dcd     0xe3510030
    dcd     0xe2804b0b
    dcd     0x13510031
    dcd     0x0a000009
    dcd     0xe5940004
    dcd     0xe3500001
    dcd     0x1a00000d
    bl      func_ov022_02083f0c
    dcd     0xe3a01000
    dcd     0xe1a02001
    bl      func_ov002_0204cdf4
    dcd     0xe3a00000
    dcd     0xe5840004
    dcd     0xea000006
    bl      func_02030788
    dcd     0xe5d51008
    dcd     0xe1510000
    dcd     0x1a000002
    dcd     0xe1a00005
    bl      func_ov022_020ad718
    dcd     0xe5840004
    dcd     0xe1a00005
    bl      func_ov022_020ad588
    dcd     0xe8bd8038
}
