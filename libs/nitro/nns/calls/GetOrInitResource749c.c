extern void G3dGlb_ComputeInvBaseMtx(void);
extern int NNS_G3dGlb[];
extern int data_0204749c[];

/* Lazy one-time init (guarded by bit 0x80 at +0xd4), then return the resource. */
int GetOrInitResource749c(void) {
    if ((NNS_G3dGlb[0x35] & 0x80) == 0) {
        G3dGlb_ComputeInvBaseMtx();
        NNS_G3dGlb[0x35] |= 0x80;
    }
    return (int)data_0204749c;
}
