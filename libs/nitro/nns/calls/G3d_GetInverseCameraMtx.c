/* Returns the inverse of the current camera matrix, computing and caching it on first use. */

extern void MTX_Inverse43(const void *src, void *dst);

extern struct { char _0[0xd4]; int field_d4; } NNS_G3dGlb;
extern char data_020473e0;
extern char data_0204746c;

void *G3d_GetInverseCameraMtx(void) {
    if (!(NNS_G3dGlb.field_d4 & 8)) {
        MTX_Inverse43(&data_020473e0, &data_0204746c);
        NNS_G3dGlb.field_d4 |= 8;
    }
    return &data_0204746c;
}
