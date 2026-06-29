extern char data_02042264[];
extern void func_0202ea48(void);
extern void func_0203c634(void);
extern void func_0203cd7c(void);
extern void func_ov107_020c9264(void);
extern void func_ov118_020d0bf4(void);

asm void func_ov118_020d0b78(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd024
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01002
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe594104c
    dcd     0xe3510000
    dcd     0x0a00000b
    dcd     0xe5942044
    dcd     0xe59f303c
    dcd     0xe28d0000
    dcd     0xe2811e19
    bl      func_0203cd7c
    dcd     0xe28d1000
    dcd     0xe2840018
    bl      func_0202ea48
    dcd     0xe2840018
    dcd     0xe284c008
    dcd     0xe890000f
    dcd     0xe88c000f
    dcd     0xe1d512d0
    dcd     0xe59f2010
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd024
    dcd     0xe8bd8030
    dcd     data_02042264
    dcd     func_ov118_020d0bf4
}
