/* Returns the inverse of the projection matrix, computing and caching it on first use. */

extern void func_02015924(void *a, void *b);
extern struct { char _0[0xd4]; int field_d4; } NNS_G3dGlb;
extern char data_0204739c[];
extern char data_0204752c[];

void *G3d_GetInverseProjMtx(void)
{
    if ((NNS_G3dGlb.field_d4 & 0x10) == 0) {
        func_02015924(data_0204739c, data_0204752c);
        NNS_G3dGlb.field_d4 |= 0x10;
    }
    return data_0204752c;
}
