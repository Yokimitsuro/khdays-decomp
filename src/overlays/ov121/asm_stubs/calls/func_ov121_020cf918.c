extern void func_01ffa724(void);
extern void func_0202f384(void);
extern void func_0203c634(void);
extern void func_ov107_020c9f48(void);
extern void func_ov121_020cf9a0(void);

asm void func_ov121_020cf918(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd00c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d1000
    dcd     0xe5940000
    dcd     0xe59003a0
    bl      func_ov107_020c9f48
    dcd     0xe5941000
    dcd     0xe1a06000
    dcd     0xe28d2000
    dcd     0xe284001c
    dcd     0xe28110a0
    bl      func_0202f384
    dcd     0xe284101c
    dcd     0xe1a00006
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe5940048
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x128dd00c
    dcd     0x18bd8078
    dcd     0xe284001c
    dcd     0xe2843028
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     func_ov121_020cf9a0
}
