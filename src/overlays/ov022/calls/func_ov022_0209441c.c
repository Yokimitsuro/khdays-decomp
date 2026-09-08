/* ov022: have the owner's three parts and its slot all finished?
 *
 * Each part has a "wanted" bit in the request mask at 0x334 and a matching
 * "done" bit in the owner's flag word. A part that is wanted but not yet done is
 * asked whether it has finished; if it has, its done bit goes up, and if it has
 * not, the answer for the whole owner is no. The slot at the actor's 0xda0 block
 * is the fourth entry of the same pair of tables, but it answers the other way
 * round: a live slot is one that has NOT finished.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Actor;

/* Ov022ActionOwner */
struct ActionOwner {
    u32 nFlags;                  /* 0x0000 */
    u8 pad0004[0x324];
    struct Actor *pActor;        /* 0x0328 */
    u8 pad032c[8];
    u8 nWanted;                  /* 0x0334 */
    u8 pad0335[11];
    u8 *apParts[3];              /* 0x0340 */
};

extern int func_ov022_020b1510(u8 *pPart);
extern int func_ov022_020b1d54(u8 *pSlot);

int func_ov022_0209441c(struct ActionOwner *pOwner)
{
    struct Actor *pActor = pOwner->pActor;
    u32 aDoneBit[3] = { 0x04, 0x08, 0x10 };
    u32 aWantBit[3] = { 0x01, 0x02, 0x04 };
    int bAllDone;
    int i;

    bAllDone = 1;
    for (i = 0; i < 3; i++) {
        if ((pOwner->nFlags & aDoneBit[i]) == 0
            && (pOwner->nWanted & aWantBit[i]) != 0) {
            if (func_ov022_020b1510(pOwner->apParts[i]) == 0) {
                bAllDone = 0;
            } else {
                pOwner->nFlags |= aDoneBit[i];
            }
        }
    }
    if ((pOwner->nFlags & 0x20) == 0 && (pOwner->nWanted & 8) != 0) {
        if (func_ov022_020b1d54((u8 *)pActor + 0xda0) != 0) {
            bAllDone = 0;
        } else {
            pOwner->nFlags |= 0x20;
        }
    }
    return bAllDone;
}
