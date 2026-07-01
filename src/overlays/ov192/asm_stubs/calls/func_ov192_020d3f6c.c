extern void func_01ffa724(void);

asm void func_ov192_020d3f6c(void) {

    dcd 0xe92d4010
    dcd 0xe5921000
    dcd 0xe5904214
    dcd 0xe1a00801
    dcd 0xe1a00820
    dcd 0xe3100001
    dcd 0x0a00000d
    dcd 0xe5940040
    dcd 0xe3500000
    dcd 0x13a00000
    dcd 0x18bd8010
    dcd 0xe3a00a01
    dcd 0xe2841014
    dcd 0xe2600000
    dcd 0xe1a02001
    bl func_01ffa724
    mov r0, #1
    dcd 0xe5840040
    dcd 0xe3a01000
    dcd 0xe5841024
    dcd 0xe8bd8010
    mov r0, #0
    dcd 0xe8bd8010
}
