extern void func_0203c650(void);
extern void func_ov107_020c7ca4(void);

asm void func_ov220_020d1e10(void) {

    dcd 0xe92d4010
    dcd 0xe1a04000
    dcd 0xe2840c01
    dcd 0xe1d00cd6
    dcd 0xe3500005
    dcd 0x159413d0
    dcd 0x13510000
    dcd 0x0a000003
    dcd 0xe594003c
    bl func_0203c650
    mov r0, #0
    dcd 0xe58403d0
    dcd 0xe2840c01
    dcd 0xe1d00cd6
    dcd 0xe3500003
    dcd 0x159413d8
    dcd 0x13510000
    dcd 0x0a000003
    dcd 0xe594003c
    bl func_0203c650
    mov r0, #0
    dcd 0xe58403d8
    dcd 0xe1a00004
    bl func_ov107_020c7ca4
    dcd 0xe8bd8010
}
