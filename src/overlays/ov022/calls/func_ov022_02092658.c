/* ov022: set up the trail effect for one actor.
 *
 * Registers the effect's animation against its own descriptor and wires two of
 * its channels to the effect's block, then loads the trail table and keeps the
 * entry for this trail count, clamped to nine. The table is freed straight away
 * because only that one entry is wanted. If the actor's own trail query answers,
 * its value, also clamped to nine, sets the entry's span.
 */

typedef unsigned char u8;
typedef unsigned short u16;

struct Anim {
    u8 pad0000[0xe0];
};

/* One trail table row, and the block the effect keeps it in. */
struct TrailEntry {
    int nA;                      /* 0x0000 */
    int nB;                      /* 0x0004 */
    u16 nSpan;                   /* 0x0008 */
    u16 nSpare00a;
    int nC;                      /* 0x000c */
};

struct Effect {
    u8 nFlags;                   /* 0x0000 */
    u8 pad0001[3];
    struct Anim anim;            /* 0x0004 */
    u8 blkChannels;              /* 0x00e4 */
    u8 pad00e5[0x27];
    struct TrailEntry trail;     /* 0x010c */
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
};

extern char data_ov022_020b2b6c[];
extern char data_ov022_020b2b7c[];

extern void func_0202a634(struct Anim *pAnim, char *pszDescriptor, int nA,
                          int nB);
extern void func_0202accc(struct Anim *pAnim, int nChannel, u8 *pBlk,
                          int nGroup);
extern struct TrailEntry *func_0201ef9c(char *pszName, int nHeap);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern int func_020358f4(int nId, int nWhat);

void func_ov022_02092658(struct Effect *pEffect, int nCount,
                         struct Actor *pActor)
{
    struct TrailEntry *pTable;
    int nSpan;

    if (nCount <= 0) {
        return;
    }
    func_0202a634(&pEffect->anim, data_ov022_020b2b6c, 1, 5);
    func_0202accc(&pEffect->anim, 0, &pEffect->blkChannels, 0);
    func_0202accc(&pEffect->anim, 2, &pEffect->blkChannels, 0);
    pTable = func_0201ef9c(data_ov022_020b2b7c, 6);
    if (nCount > 9) {
        nCount = 9;
    }
    pEffect->trail = pTable[nCount - 1];
    NNSi_FndFreeFromDefaultHeap(pTable);
    if (func_020358f4(pActor->nId, 0x18) != 0) {
        nSpan = func_020358f4(pActor->nId, 0x18);
        if (nSpan > 9) {
            nSpan = 9;
        }
        pEffect->trail.nSpan = (u16)(nSpan * 0x19a + 0x1000);
    }
    pEffect->nFlags |= 1;
}
