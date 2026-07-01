extern void func_01ff8e94(void);
extern void func_01fffde0(void);
extern void func_ov002_0206b758(void);
extern void func_ov002_0206b7a4(void);
extern void func_ov002_0206b84c(void);
extern void func_ov002_02072754(void);
extern void func_ov022_020881f8(void);
extern void func_ov022_020882f8(void);
extern void func_ov022_02088474(void);

asm void func_ov021_02080758(void)
{
    dcd     0xe92d47f0
    dcd     0xe1a06000
    bl      func_ov002_0206b7a4
    dcd     0xe3500000
    dcd     0x1a00002b
    bl      func_ov002_0206b758
    dcd     0xe3500000
    dcd     0x0a000028
    bl      func_ov002_0206b84c
    dcd     0xe59f10a0
    dcd     0xe3a04000
    dcd     0xe1500001
    dcd     0x03a05a03
    dcd     0x13a05b06
    bl      func_ov022_020882f8
    dcd     0xe3500000
    dcd     0xda00001f
    dcd     0xe1a08004
    dcd     0xe3a07801
    dcd     0xe1a0a004
    dcd     0xe1a09004
    dcd     0xe1a00004
    bl      func_01fffde0
    dcd     0xe5901000
    dcd     0xe5900004
    dcd     0xe0011007
    dcd     0xe0000008
    dcd     0xe150000a
    dcd     0x01510009
    dcd     0x1a00000e
    dcd     0xe1a00004
    bl      func_ov022_02088474
    dcd     0xe3500000
    dcd     0xba00000a
    bl      func_ov002_02072754
    dcd     0xe5d61010
    dcd     0xe1510000
    dcd     0x1a000006
    dcd     0xe1a00004
    bl      func_ov022_020881f8
    dcd     0xe2861faa
    bl      func_01ff8e94
    dcd     0xe1500005
    dcd     0xd1a00004
    dcd     0xd8bd87f0
    dcd     0xe2844001
    bl      func_ov022_020882f8
    dcd     0xe1540000
    dcd     0xbaffffe3
    dcd     0xe3e00000
    dcd     0xe8bd87f0
    dcd     0x000003b7
}
