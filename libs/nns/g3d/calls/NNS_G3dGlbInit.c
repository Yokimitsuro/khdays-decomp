/* NitroSystem G3D: initialises the global state (default polygon/material attributes, identity
 * matrices, unit scale, camera up vector). */

extern void MTX_Identity33_(void *m);
extern void MTX_Identity43_(void *m);
extern void MTX_Identity44_(void *m);

extern struct {
    int field_00;        /* 0x00 */
    int field_04;        /* 0x04 */
    char _pad08[0x48 - 0x08];
    int field_48;        /* 0x48 */
    char _pad4c[0x7c - 0x4c];
    int field_7c;        /* 0x7c */
    int field_80;        /* 0x80 */
    int field_84;        /* 0x84 */
    int field_88;        /* 0x88 */
    int field_8c;        /* 0x8c */
    int field_90;        /* 0x90 */
    char _pad94[0xb8 - 0x94];
    int field_b8;        /* 0xb8 */
    int field_bc;        /* 0xbc */
    int field_c0;        /* 0xc0 */
    int field_c4;        /* 0xc4 */
    int field_c8;        /* 0xc8 */
    int field_cc;        /* 0xcc */
    int field_d0;        /* 0xd0 */
    int field_d4;        /* 0xd4 */
    char _padd8[0x218 - 0xd8];
    int field_218;       /* 0x218 */
    int field_21c;       /* 0x21c */
    int field_220;       /* 0x220 */
    int field_224;       /* 0x224 */
    int field_228;       /* 0x228 */
    int field_22c;       /* 0x22c */
    int field_230;       /* 0x230 */
    int field_234;       /* 0x234 */
    int field_238;       /* 0x238 */
} NNS_G3dGlb;

extern char data_0204739c[];   /* &NNS_G3dGlb + 0x08 */
extern char data_020473e0[];   /* &NNS_G3dGlb + 0x4C */
extern char data_02047428[];   /* &NNS_G3dGlb + 0x94 */

void NNS_G3dGlbInit(void) {
    NNS_G3dGlb.field_00 = 0x17101610;
    NNS_G3dGlb.field_04 = 0;
    NNS_G3dGlb.field_48 = 2;
    NNS_G3dGlb.field_7c = 0x60293130;
    NNS_G3dGlb.field_90 = 0x002a1b19;
    MTX_Identity43_(&data_020473e0);
    MTX_Identity44_(&data_0204739c);
    NNS_G3dGlb.field_80 = 0x4210c210;
    NNS_G3dGlb.field_84 = 0x4210c210;
    NNS_G3dGlb.field_88 = 0x001f008f;
    NNS_G3dGlb.field_8c = (int)0xbfff0000;
    NNS_G3dGlb.field_b8 = 0;
    NNS_G3dGlb.field_bc = 0;
    NNS_G3dGlb.field_c0 = 0;
    MTX_Identity33_(&data_02047428);
    NNS_G3dGlb.field_c4 = 0x1000;
    NNS_G3dGlb.field_c8 = 0x1000;
    NNS_G3dGlb.field_cc = 0x1000;
    NNS_G3dGlb.field_d0 = 0;
    NNS_G3dGlb.field_d4 = 0;
    NNS_G3dGlb.field_220 = 0;
    NNS_G3dGlb.field_21c = 0;
    NNS_G3dGlb.field_218 = 0;
    NNS_G3dGlb.field_22c = 0;
    NNS_G3dGlb.field_224 = 0;
    NNS_G3dGlb.field_228 = 0x1000;
    NNS_G3dGlb.field_234 = 0;
    NNS_G3dGlb.field_230 = 0;
    NNS_G3dGlb.field_238 = -0x1000;
}
