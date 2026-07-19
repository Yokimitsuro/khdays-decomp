extern char *data_ov008_02090fac;
extern int func_ov008_02082274(int id);
extern void func_02013484(void *dst, void *src, unsigned short w, unsigned short h,
                          int x, int y, int cw, int ch, int srcW, int srcH);

/* Blits one queued image into its VRAM bank and marks the bank dirty. A -1 in the size fields
 * means "take it from the source header". */
void func_ov008_020822fc(char *req, int external) {
    char *st = *(char **)&data_ov008_02090fac;
    int bank = func_ov008_02082274(*(int *)(req + 0x10));
    char *src;
    char *dst;
    int srcW;
    int srcH;
    if (bank < 0) {
        return;
    }
    if (bank >= 7) {
        return;
    }
    dst = st + 0xa8 + bank * 0x600;
    if (external != 0) {
        src = *(char **)(*(char **)(req + 0x18) + 8);
    } else {
        src = *(char **)(st + 0x2aa8);
    }
    srcW = *(short *)(req + 0xa);
    if (srcW == -1) {
        srcW = (unsigned int)*(unsigned short *)(*(char **)(*(char **)(req + 0x18) + 8)) >> 3;
    }
    srcH = *(short *)(req + 0xc);
    if (srcH == -1) {
        srcH = (unsigned int)*(unsigned short *)(*(char **)(*(char **)(req + 0x18) + 8) + 2) >> 3;
    }
    func_02013484(dst, src,
                  *(unsigned short *)(req + 6), *(unsigned short *)(req + 8),
                  *(short *)(req + 2), *(short *)(req + 4), 0x20, 0x18, srcW, srcH);
    *(int *)(st + 0x2aac) |= 1 << bank;
}
