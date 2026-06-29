extern void func_01fff774(void);
extern void func_02014dc4(void);
extern void func_0202accc(void);

asm void func_ov048_020b4050(void)
{
    dcd     0xe92d41f0
    dcd     0xe3a05000
    dcd     0xe1a06000
    dcd     0xe1a00801
    dcd     0xe1a08840
    dcd     0xe1a04005
    dcd     0xe1a07005
    dcd     0xe0860105
    dcd     0xe5901258
    dcd     0xe3510000
    dcd     0x0a000003
    dcd     0xe2860f9b
    bl      func_02014dc4
    dcd     0xe0860105
    dcd     0xe5804258
    dcd     0xe1a01805
    dcd     0xe5962354
    dcd     0xe1a03008
    dcd     0xe2860f93
    dcd     0xe1a01821
    bl      func_0202accc
    dcd     0xe1a01805
    dcd     0xe1a02007
    dcd     0xe2860f93
    dcd     0xe1a01821
    bl      func_01fff774
    dcd     0xe2855001
    dcd     0xe3550005
    dcd     0xbaffffe9
    dcd     0xe8bd81f0
}
