/* Composes the global base matrix with the camera and scale and stores its inverse. */

extern void MTX_Concat43(const void *a, const void *b, void *out);
extern void MTX_ScaleApply43(const void *src, void *dst, int x, int y, int z);
extern void MTX_Inverse43(const void *src, void *dst);

extern char data_02047428[];
extern char data_020473e0[];
extern char data_0204749c[];
extern char data_020474cc[];
extern struct { char _0[0xc4]; int field_c4; int field_c8; int field_cc; } NNS_G3dGlb;

void G3dGlb_ComputeInvBaseMtx(void) {
    MTX_Concat43(&data_02047428, &data_020473e0, &data_0204749c);
    MTX_ScaleApply43(&data_0204749c, &data_0204749c, NNS_G3dGlb.field_c4, NNS_G3dGlb.field_c8, NNS_G3dGlb.field_cc);
    MTX_Inverse43(&data_0204749c, &data_020474cc);
}
