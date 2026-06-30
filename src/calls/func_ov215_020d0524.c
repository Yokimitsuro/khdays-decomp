extern void func_ov107_020c7ca4(void);
extern void func_ov215_020d028c(void);

asm void func_ov215_020d0524(void) {

    dcd 0xe92d4010
    dcd 0xe1a04000
    dcd 0xe2841c01
    dcd 0xe1d11cd6
    dcd 0xe3510005
    dcd 0x0a000001
    bl func_ov215_020d028c
    dcd 0xea000015
    dcd 0xe5940454
    dcd 0xe3500000
    dcd 0x0a000007
    dcd 0xe5942450
    dcd 0xe5d401c4
    dcd 0xe592105c
    dcd 0xe2000002
    dcd 0xe3c11002
    dcd 0xe1a00f80
    dcd 0xe1810f20
    dcd 0xe582005c
    dcd 0xe5940464
    dcd 0xe3500000
    dcd 0x0a000007
    dcd 0xe5942460
    dcd 0xe5d401c4
    dcd 0xe592105c
    dcd 0xe2000002
    dcd 0xe3c11002
    dcd 0xe1a00f80
    dcd 0xe1810f20
    dcd 0xe582005c
    dcd 0xe1a00004
    bl func_ov107_020c7ca4
    dcd 0xe8bd8010
}
