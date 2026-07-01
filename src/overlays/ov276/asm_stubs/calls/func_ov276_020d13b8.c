extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov276_020d0cdc(void);
extern void func_ov276_020d1420(void);

asm void func_ov276_020d13b8(void) {

    dcd 0xe92d4038
    dcd 0xe1a05000
    dcd 0xe8950011
    dcd 0xe590102c
    dcd 0xe594204c
    dcd 0xe59f0044
    dcd 0xe0821001
    dcd 0xe584104c
    dcd 0xe1510000
    dcd 0xb8bd8038
    dcd 0xe3a01000
    dcd 0xe5940000
    dcd 0xe1a02001
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a01000
    bl func_ov276_020d0cdc
    dcd 0xe3a00000
    dcd 0xe584004c
    dcd 0xe1d512d0
    dcd 0xe59f200c
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe8bd8038
    dcd 0x00000666
    dcd func_ov276_020d1420
}
