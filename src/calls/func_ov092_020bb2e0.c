extern void WM_EndKeySharing_0x020b15a4(void);
extern void data_ov092_020bc4e0(void);

asm void func_ov092_020bb2e0(void)
{
    dcd     0xe92d4ff8
    dcd     0xe59f1090
    dcd     0xe1a0a000
    dcd     0xe5910000
    dcd     0xe28a4a02
    dcd     0xe2800f65
    dcd     0xe280bb0b
    dcd     0xe3a06000
    dcd     0xe5945644
    dcd     0xe1a08006
    dcd     0xe28b9f4d
    dcd     0xe595203c
    dcd     0xe594063c
    dcd     0xe1a01009
    dcd     0xe0827008
    bl      WM_EndKeySharing_0x020b15a4
    dcd     0xe2866001
    dcd     0xe5879130
    dcd     0xe356000c
    dcd     0xe2888f72
    dcd     0xe2899024
    dcd     0xbafffff4
    dcd     0xe28a5a02
    dcd     0xe3a04000
    dcd     0xe5956644
    dcd     0xe1a08004
    dcd     0xe28b9fb9
    dcd     0xe596206c
    dcd     0xe5950640
    dcd     0xe1a01009
    dcd     0xe0827008
    bl      WM_EndKeySharing_0x020b15a4
    dcd     0xe2844001
    dcd     0xe5879130
    dcd     0xe3540002
    dcd     0xe2888f72
    dcd     0xe2899024
    dcd     0xbafffff4
    dcd     0xe8bd8ff8
    dcd     data_ov092_020bc4e0
}
