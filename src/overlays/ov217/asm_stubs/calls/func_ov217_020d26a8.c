extern void data_02042270(void);
extern void func_02020400(void);
extern void func_0202f188(void);

asm void func_ov217_020d26a8(void) {

    dcd 0xe92d4010
    dcd 0xe1a04000
    dcd 0xe5942004
    dcd 0xe3a00038
    dcd 0xe0030092
    dcd 0xe5940000
    dcd 0xe3a02b05
    dcd 0xe590c090
    dcd 0xe3a00b02
    dcd 0xe08ce003
    dcd 0xe78c2003
    dcd 0xe58e0004
    dcd 0xe28e302c
    dcd 0xe8910007
    dcd 0xe8830007
    dcd 0xe59f1020
    dcd 0xe59f2020
    dcd 0xe28e0008
    bl func_0202f188
    dcd 0xe8940005
    dcd 0xe590108c
    dcd 0xe2820001
    bl func_02020400
    dcd 0xe5841004
    dcd 0xe8bd8010
    dcd data_02042270
    dcd 0x00001922
}
