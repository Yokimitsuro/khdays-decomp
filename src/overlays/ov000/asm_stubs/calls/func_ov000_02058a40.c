typedef unsigned short  u16;
typedef unsigned int u32;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

typedef struct GXBackgroundControlBank {
    vu16 bg0;
    vu16 bg1;
    vu16 bg2;
    vu16 bg3;
} GXBackgroundControlBank;

typedef struct GXEngine2dRegisters {
    vu32 displayControl;
    u32 pad_04;
    GXBackgroundControlBank backgrounds;
} GXEngine2dRegisters;

extern void func_0201e1d0(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *destination, unsigned int size);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForOBJ(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void func_020056b4(int enabled, int field, int mode);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForSubOBJ(int bank);
extern void GX_SetBankForSubBGExtPltt(int bank);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void GXS_SetGraphicsMode(int mode);

asm void func_ov000_02058a40(void) {
    dcd 0xe92d4008
    bl func_0201e1d0
    bl G2_GetBG1ScrPtr
    dcd 0xe1a01000
    dcd 0xe3a00000
    dcd 0xe3a02b02
    bl MIi_CpuClearFast
    bl G2_GetBG2ScrPtr
    dcd 0xe1a01000
    dcd 0xe3a00000
    dcd 0xe3a02b02
    bl MIi_CpuClearFast
    bl G2_GetBG3ScrPtr
    dcd 0xe1a01000
    dcd 0xe3a00000
    dcd 0xe3a02b02
    bl MIi_CpuClearFast
    dcd 0xe3a00001
    bl GX_SetBankForBG
    dcd 0xe3a00002
    bl GX_SetBankForOBJ
    dcd 0xe3a00000
    bl GX_SetBankForBGExtPltt
    dcd 0xe3a03301
    dcd 0xe5932000
    dcd 0xe59f1168
    dcd 0xe3a00001
    dcd 0xe0021001
    dcd 0xe3811010
    dcd 0xe3811602
    dcd 0xe5831000
    dcd 0xe3a01000
    dcd 0xe1a02000
    bl func_020056b4
    dcd 0xe59f3148
    dcd 0xe3a02301
    dcd 0xe1d310b0
    dcd 0xe3a00004
    dcd 0xe3c11003
    dcd 0xe3811001
    dcd 0xe1c310b0
    dcd 0xe1d310b0
    dcd 0xe3c11003
    dcd 0xe3811002
    dcd 0xe1c310b0
    dcd 0xe1d310b4
    dcd 0xe3c11003
    dcd 0xe3811003
    dcd 0xe1c310b4
    dcd 0xe5921000
    dcd 0xe3c11c1f
    dcd 0xe3811c1e
    dcd 0xe5821000
    bl GX_SetBankForSubBG
    dcd 0xe3a00008
    bl GX_SetBankForSubOBJ
    dcd 0xe3a00000
    bl GX_SetBankForSubBGExtPltt
    dcd 0xe3a00000
    bl GX_SetBankForSubOBJExtPltt
    dcd 0xe59f30e4
    dcd 0xe59f10d8
    dcd 0xe5932000
    dcd 0xe3a00000
    dcd 0xe0021001
    dcd 0xe3811010
    dcd 0xe3811602
    dcd 0xe5831000
    bl GXS_SetGraphicsMode
    dcd 0xe59f00c4
    dcd 0xe59f30c4
    dcd 0xe1d010b0
    dcd 0xe240c008
    dcd 0xe59f20ac
    dcd 0xe3c11003
    dcd 0xe3811001
    dcd 0xe1c010b0
    dcd 0xe1d010b2
    dcd 0xe3c11003
    dcd 0xe3811002
    dcd 0xe1c010b2
    dcd 0xe1d010b6
    dcd 0xe3c11003
    dcd 0xe3811003
    dcd 0xe1c010b6
    dcd 0xe59c1000
    dcd 0xe3c11c1f
    dcd 0xe3811c1b
    dcd 0xe58c1000
    dcd 0xe1d310b0
    dcd 0xe3811902
    dcd 0xe1c310b0
    dcd 0xe1d210b0
    dcd 0xe2011043
    dcd 0xe3811e41
    dcd 0xe1c210b0
    dcd 0xe1d210b2
    dcd 0xe2011043
    dcd 0xe3811f82
    dcd 0xe1c210b2
    dcd 0xe1d210b4
    dcd 0xe2011043
    dcd 0xe3811004
    dcd 0xe1c210b4
    dcd 0xe1d010b0
    dcd 0xe2011043
    dcd 0xe3811e21
    dcd 0xe1c010b0
    dcd 0xe1d010b2
    dcd 0xe2011043
    dcd 0xe3811f42
    dcd 0xe1c010b2
    dcd 0xe1d010b6
    dcd 0xe2011043
    dcd 0xe3811008
    dcd 0xe1c010b6
    dcd 0xe8bd8008
    dcd 0xffcfffef
    dcd 0x0400000a
    dcd 0x04001000
    dcd 0x04001008
    dcd 0x04000304
}
