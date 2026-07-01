extern void func_01ffa724(void);
extern void func_0202f384(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c9f48(void);
extern void func_ov121_020cfad0(void);

asm void func_ov121_020cfa14(void)
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
    dcd     0xe5940000
    dcd     0xe3a01009
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    mov r0, #0
    dcd     0xe5840040
    dcd     0xe5944000
    dcd     0xe59f2038
    dcd     0xe1d436b0
    dcd     0xe1a00005
    dcd     0xe1a01803
    dcd     0xe1a01c21
    dcd     0xe3c11040
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe3c33cff
    dcd     0xe1a01c01
    dcd     0xe1831821
    dcd     0xe1c416b0
    dcd     0xe1d512d0
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     func_ov121_020cfad0
}
