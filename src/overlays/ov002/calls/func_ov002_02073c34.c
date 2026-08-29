typedef unsigned char u8;

typedef struct Ov002Vec3 {
    int x, y, z;
} Ov002Vec3;

/* One object slot, 0x18 bytes. */
typedef struct Ov002ObjectSlot {
    void *pObject;                      /* +0x00 */
    Ov002Vec3 vAt;                      /* +0x04 */
    int nMode;                          /* +0x10 */
    u8 bEntryIndex;                     /* +0x14 */
    char pad15[3];
} Ov002ObjectSlot;

typedef struct Ov002ObjectContext {
    char pad00[0x44];
    Ov002ObjectSlot *pSlots;            /* +0x44 */
} Ov002ObjectContext;

/* The block the positional animation start takes: a place and the mode. */
typedef struct Ov002AnimAt {
    Ov002Vec3 vAt;                      /* +0x00 */
    int nMode;                          /* +0x0c */
} Ov002AnimAt;

extern Ov002ObjectContext *data_ov002_0207fa14;

extern int func_ov107_020cb5ac(void);
extern int func_ov107_020cb268(Ov002AnimAt *pAt);
extern void func_ov107_020c1c18(void *pObject, int nAnim, int nFlag);
extern void func_ov002_02073ed0(int nKey, int nParam, int nFlag);

/* Start a slot's animation and record where it was started from.
 *
 * Mode zero takes the plain animation; any other mode takes the positional
 * one, which is handed the place and the mode together in a block on the
 * stack. Either way the animation goes to the slot's object. The place is then
 * copied into the slot when the caller gave one, the mode and the key are
 * stamped in, and the key's node is made visible.
 */
void func_ov002_02073c34(int nIndex, int nKey, int nMode, Ov002Vec3 *pAt,
                         int nParam)
{
    Ov002ObjectContext *pCtx;
    Ov002AnimAt at;
    int nAnim;

    pCtx = data_ov002_0207fa14;
    if (nMode == 0) {
        nAnim = func_ov107_020cb5ac();
        func_ov107_020c1c18(pCtx->pSlots[nIndex].pObject, nAnim, 1);
    } else {
        at.vAt.x = pAt->x;
        at.vAt.y = pAt->y;
        at.vAt.z = pAt->z;
        at.nMode = nMode;
        nAnim = func_ov107_020cb268(&at);
        func_ov107_020c1c18(pCtx->pSlots[nIndex].pObject, nAnim, 1);
    }

    if (pAt != 0) {
        pCtx->pSlots[nIndex].vAt = *pAt;
    }
    pCtx->pSlots[nIndex].nMode = nMode;
    pCtx->pSlots[nIndex].bEntryIndex = (u8)nKey;
    func_ov002_02073ed0(nKey, nParam, -1);
}
