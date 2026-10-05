/* Returns the inverse camera x inverse projection matrix, computing and caching it on first use. */

extern void *G3d_GetInverseCameraMtx(void);
extern void *G3d_GetInverseProjMtx(void);
extern void MTX_Copy43To44_(const void *src, void *dst);
extern void MTX_Concat44(const void *a, const void *b, void *out);

extern struct { char _0[0xd4]; int field_d4; } NNS_G3dGlb;
extern char data_0204756c[];

void *G3d_GetInverseViewProjMtx(void) {
    int m44[0x10];

    if (!(NNS_G3dGlb.field_d4 & 0x40)) {
        void *m43 = G3d_GetInverseCameraMtx();
        void *m44_src = G3d_GetInverseProjMtx();

        MTX_Copy43To44_(m43, m44);
        MTX_Concat44(m44_src, m44, data_0204756c);
        NNS_G3dGlb.field_d4 |= 0x40;
    }

    return data_0204756c;
}
