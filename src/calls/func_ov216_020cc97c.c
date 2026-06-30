extern void func_02014b5c(void);
extern void func_0202a388(void);
extern void func_0202a440(void);
extern void func_0203b9ac(void);
extern void func_0203b9fc(void);
extern void func_0203c7ac(void);

asm void func_ov216_020cc97c(void) {

    dcd 0xe92d41f0
    dcd 0xe1a08000
    dcd 0xe1a05003
    dcd 0xe1a00005
    dcd 0xe5984088
    dcd 0xe1a07001
    dcd 0xe1a06002
    bl func_0202a440
    dcd 0xe3a00000
    dcd 0xe585000c
    dcd 0xe5941078
    dcd 0xe2840020
    bl func_02014b5c
    dcd 0xe1a01004
    dcd 0xe1a02007
    dcd 0xe1a00005
    dcd 0xe3a0300c
    bl func_0202a388
    dcd 0xe1a01005
    dcd 0xe1a00008
    bl func_0203b9ac
    dcd 0xe1a03006
    dcd 0xe1a00008
    dcd 0xe3a01000
    dcd 0xe1a02001
    bl func_0203b9fc
    dcd 0xe1a00008
    dcd 0xe3a01000
    bl func_0203c7ac
    dcd 0xe8bd81f0
}
