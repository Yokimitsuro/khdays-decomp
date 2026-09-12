typedef unsigned short u16;

extern void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame);
extern void func_0202af1c(u16 *p);

void func_ov016_020815e8(char *self, int type, int field624, int field620) {
    u16 flags;
    short *pAnim;

    *(char *)(self + 0x61e) = (char)type;
    *(int *)(self + 0x624) = field624;
    *(int *)(self + 0x620) = field620;

    flags = *(u16 *)(self + 0x12);
    pAnim = (short *)(self + 0x4a8);
    if ((flags & 4) != 0) {
        if ((flags & 4) != 0) {
            func_ov002_0207c618(pAnim,
                                 *(signed char *)(self + 0x61e),
                                 *(int *)(self + 0x620));
            func_0202af1c((u16 *)pAnim);
        }
    }
}
