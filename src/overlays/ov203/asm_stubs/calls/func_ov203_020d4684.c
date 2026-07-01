extern void INITi_CpuClear32_0x01ff86fc(void);
extern void data_02042264(void);
extern void func_0202ed60(void);
extern void func_0202ef54(void);
extern void func_0202f188(void);
extern void func_0203c9d0(void);
extern void func_0203d040(void);

asm void func_ov203_020d4684(void) {

    dcd 0xe92d4038
    dcd 0xe24dd020
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe5940000
    dcd 0xe5d001c4
    dcd 0xe3100002
    dcd 0x1a000005
    dcd 0xe5940008
    dcd 0xe594100c
    dcd 0xe5942010
    dcd 0xe3a03000
    bl func_0203d040
    dcd 0xe5840008
    dcd 0xe5941000
    dcd 0xe1d106b0
    dcd 0xe1a00c00
    dcd 0xe1a00c20
    dcd 0xe3100040
    dcd 0x1a000014
    dcd 0xe5d1017a
    dcd 0xe1a00f80
    dcd 0xe1b00fa0
    dcd 0x0a000010
    dcd 0xe5942008
    dcd 0xe59f107c
    dcd 0xe28d0010
    bl func_0202f188
    dcd 0xe5942000
    dcd 0xe59f106c
    dcd 0xe28d0000
    dcd 0xe2822f49
    bl func_0202ed60
    dcd 0xe28d0000
    dcd 0xe28d2010
    dcd 0xe1a01000
    bl func_0202ef54
    dcd 0xe5940000
    dcd 0xe28d1000
    dcd 0xe28000a0
    bl func_0203c9d0
    dcd 0xe5941030
    dcd 0xe3510000
    dcd 0xda000003
    dcd 0xe5950000
    dcd 0xe590002c
    dcd 0xe0410000
    dcd 0xe5840030
    dcd 0xe4940014
    dcd 0xe28030f0
    dcd 0xe8940007
    dcd 0xe8830007
    dcd 0xe1a01004
    dcd 0xe3a00000
    dcd 0xe3a0200c
    bl INITi_CpuClear32_0x01ff86fc
    dcd 0xe28dd020
    dcd 0xe8bd8038
    dcd data_02042264
}
