extern void WM_EndKeySharing_0x020b15a4(void);
extern char data_ov074_020b9b80[];

asm void func_ov074_020b9150(void)
{
    dcd     0xe92d43f8
    dcd     0xe59f1048
    dcd     0xe2804a02
    dcd     0xe5910000
    dcd     0xe3a06000
    dcd     0xe2800f75
    dcd     0xe5945644
    dcd     0xe1a08006
    dcd     0xe2809b0b
    dcd     0xe595203c
    dcd     0xe594063c
    dcd     0xe1a01009
    dcd     0xe0827008
    bl      WM_EndKeySharing_0x020b15a4
    dcd     0xe2866001
    dcd     0xe5879130
    dcd     0xe3560002
    dcd     0xe2888f72
    dcd     0xe2899024
    dcd     0xbafffff4
    dcd     0xe8bd83f8
    dcd     data_ov074_020b9b80
}
