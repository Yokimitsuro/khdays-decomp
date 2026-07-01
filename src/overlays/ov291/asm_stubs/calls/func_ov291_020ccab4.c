extern char data_02041dc8[];
extern char data_02042264[];
extern void func_01fffd70(void);
extern void func_01fffd8c(void);
extern void func_0202f188(void);
extern void func_0203c9d0(void);
extern void func_0203d040(void);
extern void func_ov002_02056a98(void);
extern void func_ov022_02083f0c(void);
extern void func_ov022_02083f5c(void);
extern void func_ov022_02086834(void);
extern void func_ov291_020cca78(void);

asm void func_ov291_020ccab4(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd010
    dcd     0xe5906004
    dcd     0xe3a07000
    dcd     0xe596201c
    dcd     0xe9960003
    dcd     0xe1a03007
    bl      func_0203d040
    dcd     0xe59f1134
    dcd     0xe5860004
    dcd     0xe1a02000
    dcd     0xe28d0000
    bl      func_0202f188
    dcd     0xe5960000
    dcd     0xe28d1000
    dcd     0xe28000a0
    bl      func_0203c9d0
    dcd     0xe5960000
    dcd     0xe2865010
    dcd     0xe28040f0
    dcd     0xe8950007
    dcd     0xe8840007
    dcd     0xe59f3100
    dcd     0xe8930007
    dcd     0xe8850007
    dcd     0xe5960030
    dcd     0xe3500000
    dcd     0x128dd010
    dcd     0x18bd8ff8
    dcd     0xe5960000
    dcd     0xe5909004
    dcd     0xe28900a8
    bl      func_01fffd70
    dcd     0xe3500000
    dcd     0x01a0a007
    dcd     0x1590a000
    dcd     0xe35a0000
    dcd     0x0a000025
    dcd     0xe3a0b000
    dcd     0xe3a05001
    dcd     0xe1a0400b
    dcd     0xe59a018c
    dcd     0xe5902000
    dcd     0xe5901004
    mov r0, #0
    dcd     0xe0010000
    dcd     0xe2022801
    dcd     0xe150000b
    dcd     0x01520004
    dcd     0x1a000012
    bl      func_ov022_02083f0c
    bl      func_ov022_02083f5c
    dcd     0xe1a08000
    dcd     0xe59a018c
    bl      func_ov291_020cca78
    dcd     0xe3500000
    dcd     0x0a000008
    dcd     0xe5960034
    dcd     0xe3500000
    dcd     0x1a000005
    dcd     0xe1a00008
    dcd     0xe3a01001
    bl      func_ov022_02086834
    mov r0, #1
    bl      func_ov002_02056a98
    dcd     0xe5865034
    dcd     0xe2870001
    dcd     0xe1a00c00
    dcd     0xe1a07c40
    dcd     0xe28900a8
    bl      func_01fffd8c
    dcd     0xe3500000
    dcd     0x03a0a000
    dcd     0x1590a000
    dcd     0xe35a0000
    dcd     0x1affffdc
    dcd     0xe3570000
    dcd     0x128dd010
    dcd     0x18bd8ff8
    dcd     0xe3a01000
    dcd     0xe1a00008
    dcd     0xe5861034
    bl      func_ov022_02086834
    mov r0, #0
    bl      func_ov002_02056a98
    dcd     0xe28dd010
    dcd     0xe8bd8ff8
    dcd     data_02042264
    dcd     data_02041dc8
}
