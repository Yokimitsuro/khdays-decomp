extern void func_01fff774(void);
extern void func_02016ae8(void);

asm void func_ov090_020bc704(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06001
    dcd     0xe3a01000
    dcd     0xe3a03005
    dcd     0xe1a02001
    dcd     0xe2860028
    dcd     0xe5863024
    bl      func_01fff774
    dcd     0xe2860028
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe59f0040
    dcd     0xe3a05000
    dcd     0xe58600e0
    dcd     0xe58600dc
    dcd     0xe58600d8
    dcd     0xe1a04005
    dcd     0xe59600a0
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_02016ae8
    dcd     0xe2855001
    dcd     0xe355000a
    dcd     0xbafffff8
    dcd     0xe59600a0
    dcd     0xe3a01007
    dcd     0xe3a02003
    bl      func_02016ae8
    dcd     0xe8bd8070
    dcd     0x00000ccd
}
