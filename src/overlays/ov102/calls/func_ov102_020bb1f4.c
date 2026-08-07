/* Spawns the ov102 panel's effect instances around the actor. Builds a rotation matrix
 * from the link's facing angle -- biased by 0x8000 and folded to 12 bits to index the
 * shared sin/cos pair table -- then, for each instance, takes the next offset from a
 * ring of candidate offsets (four when the panel's block is idle, eight when it is not),
 * rotates it into world space, adds it to the actor's anchor position and files a spawn
 * request. The ring cursor at the block's +0x124 advances once per instance, so
 * consecutive calls walk the ring.
 *
 * The stack objects are grouped into ONE frame struct, the same way the ov031 copy of
 * this spawn-request idiom does it. That is what pins the layout: the two rings, the
 * matrix, the anchor, the rotated offset and the request are all at fixed offsets of a
 * 0xf8-byte frame, and declaring them as separate locals lets mwcc reorder them. */
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct SpawnRing4 {
    struct VecFx32 v[4];
};

struct SpawnRing8 {
    struct VecFx32 v[8];
};

struct PanelSpawnReq {
    struct VecFx32 vPos;
    short sx;
    short sy;
    short sz;
    short nScale;
    int f14;
    int f18;
    int f1c;
    int f20;
    int f24;
    int f28;
};

struct SpawnFrame {
    struct SpawnRing4 ring4;
    int mtx[9];
    struct VecFx32 vAnchor;
    struct VecFx32 vOffset;
    struct PanelSpawnReq req;
    struct SpawnRing8 ring8;
};

extern void MTX_RotY33_(int *mtx, int nCos, int nSin);
extern void MTX_MultVec33(struct VecFx32 *pIn, int *mtx, struct VecFx32 *pOut);
extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
/* _s32_div_f: the MetroWerks signed divide. Quotient in r0, REMAINDER IN r1, so the
 * 64-bit return type is how the remainder is reached from C. Writing `a % b` emits
 * byte-identical code but names the reloc _s32_div_f, which symbols.txt does not
 * define, so the helper is called by its address instead. */
extern long long func_02020400(int a, int b);
extern int func_020307f4(int a);
extern void func_ov022_02091324(char *self, struct PanelSpawnReq *pReq);

extern struct SpawnRing4 data_ov102_020bb7ec;
extern struct SpawnRing8 data_ov102_020bb81c;
extern char *data_ov102_020bb920;
extern short data_0203d210[];

void func_ov102_020b3c54(char *self)
{
    struct SpawnFrame f;
    char *blk;
    int i;
    int nCount;
    int nRingSize;
    struct VecFx32 *pRing;
    int nIdx;

    f.ring4 = data_ov102_020bb7ec;
    blk = data_ov102_020bb920 + 0xc50 + 0x2000;
    f.ring8 = data_ov102_020bb81c;

    nIdx = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
    MTX_RotY33_(f.mtx, -data_0203d210[nIdx * 2], -data_0203d210[nIdx * 2 + 1]);

    f.vAnchor = *(struct VecFx32 *)(self + 0x8c + 0x400);

    if (*(int *)blk == 0) {
        nRingSize = 4;
        pRing = f.ring4.v;
        nCount = 1;
    } else {
        pRing = f.ring8.v;
        nRingSize = 8;
        nCount = 2;
    }

    for (i = 0; i < nCount; i++) {
        f.req.sz = 0;
        f.req.sy = f.req.sz;
        f.req.sx = f.req.sy;

        /* The high half of the 64-bit return is r1, the remainder: this means
         * pRing[*(int *)(blk + 0x124) % nRingSize]. */
        MTX_MultVec33(&pRing[(int)(func_02020400(*(int *)(blk + 0x124),
                                                 nRingSize) >> 32)],
                      f.mtx, &f.vOffset);
        VEC_Add(&f.vAnchor, &f.vOffset, &f.req.vPos);

        f.req.f14 = 0;
        f.req.f1c = 1;
        f.req.f20 = 0;
        f.req.f18 = 7;
        f.req.f24 = func_020307f4(3);
        f.req.f28 = 0;
        f.req.nScale = 0x1400;
        if (*(int *)blk != 0) {
            f.req.f28 = 1;
            f.req.nScale = 0xd00;
        }

        func_ov022_02091324(self, &f.req);
        if ((int)(*(long long *)self & 0x10000) == 0) {
            *(self + 0x47a) = 3;
            *(self + 0x47b) = 0;
        }
        *(int *)(blk + 0x124) = *(int *)(blk + 0x124) + 1;
    }
}
