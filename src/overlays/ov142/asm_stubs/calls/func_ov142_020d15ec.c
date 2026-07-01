extern void func_0203d15c(void);
extern void func_ov107_020c6624(void);
extern void func_ov142_020d1620(void);

asm void func_ov142_020d15ec(void) {

    dcd 0xe92d4038
    dcd 0xe1a05000
    dcd 0xe3a00e3a
    bl func_0203d15c
    dcd 0xe1a04000
    dcd 0xe59f2014
    dcd 0xe5845398
    dcd 0xe3a01000
    dcd 0xe584218c
    bl func_ov107_020c6624
    dcd 0xe1a00004
    dcd 0xe8bd8038
    dcd func_ov142_020d1620
}
