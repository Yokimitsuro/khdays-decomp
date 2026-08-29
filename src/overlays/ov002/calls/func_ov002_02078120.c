typedef signed int s32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct Ov002Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Ov002Vec3;

/* The collision cast block, as the matched sources in src/calls spell it. */
typedef struct CollCastParams {
    Ov002Vec3 *origin;
    Ov002Vec3 *direction;
    s32 radius;
    u16 directionIsUnit;
    u16 flags;
    void *exclude;
} CollCastParams;

/* Only the fields this routine touches; the rest of the element is modelled in
 * Ghidra as Ov002PieceElement. */
typedef struct Ov002PieceElement {
    char pad0000[0x2c];
    u8 nColumn;                     /* +0x2c */
    u8 nRow;                        /* +0x2d */
    u16 nPieceId;                   /* +0x2e */
    char pad0030[2];
    u8 nSlot;                       /* +0x32 */
} Ov002PieceElement;

/* Likewise only the trailing spot table; aSpots holds the last place each spot
 * was spawned at. */
typedef struct Ov002SpotStage {
    char pad0000[0x2528];
    Ov002Vec3 aSpots[1];            /* +0x2528 */
} Ov002SpotStage;

/* The stage pointer sits one word into the holder, and the overlay's own
 * sources reach it by indexing rather than through a named field. */
extern Ov002SpotStage *data_ov002_0207fa28[];

extern int func_ov002_0207285c(int nSlot);
extern void *func_0202c208(u16 nId, CollCastParams *pParams);
extern void func_01ffd144(void *pObject, Ov002Vec3 *pOut, Ov002Vec3 *pIn);
extern void VEC_Add(const Ov002Vec3 *a, const Ov002Vec3 *b, Ov002Vec3 *ab);
extern void func_ov002_02077b64(int nRow, int nColumn, int nId, int nSlot,
                                Ov002Vec3 *pAt, int nKind, int nFlags);

/* Settle where a board slot's marker belongs and hand it to the placer.
 *
 * The marker starts at the slot's own spot position and is cast straight down.
 * A first hit moves the start point onto the surface and the cast is retried
 * from a little above it; if that second cast misses, the surface point and the
 * spot position are added together. With no hit at all the spot position stands
 * as it is.
 */
void func_ov002_02078120(Ov002PieceElement *pSlot)
{
    CollCastParams params;
    Ov002Vec3 vDown;
    Ov002Vec3 vAt;
    void *pHit;
    int nId;

    nId = func_ov002_0207285c(pSlot->nSlot);

    params.directionIsUnit = 0;
    params.exclude = 0;
    params.flags = 0xf;
    params.origin = &data_ov002_0207fa28[1]->aSpots[pSlot->nRow];
    vDown.z = 0;
    vDown.x = 0;
    vDown.y = -0x64000;
    params.direction = &vDown;

    pHit = func_0202c208(nId, &params);
    if (pHit != 0) {
        func_01ffd144(*(void **)((char *)pHit + 0xc), &vDown, &vDown);
        vDown.y += 0x1000;
        if (func_0202c208(nId, &params) == 0) {
            VEC_Add(&vDown, &data_ov002_0207fa28[1]->aSpots[pSlot->nRow],
                    &vAt);
        } else {
            vAt = data_ov002_0207fa28[1]->aSpots[pSlot->nRow];
        }
    } else {
        vAt = data_ov002_0207fa28[1]->aSpots[pSlot->nRow];
    }

    func_ov002_02077b64(pSlot->nRow, pSlot->nColumn, pSlot->nPieceId,
                        pSlot->nSlot, &vAt, 1, 0);
}
