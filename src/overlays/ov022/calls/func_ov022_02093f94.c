/* ov022: set up the arm effect for one actor.
 *
 * Registers the effect's animation against its own descriptor and wires its four
 * channels to the effect's block, then loads the arm table and keeps the entry
 * for this arm count, clamped to nine. The table is freed straight away because
 * only that one entry is wanted. Two per-id queries decide the remaining two
 * flags.
 */

typedef unsigned char u8;
typedef unsigned int u32;

struct Anim {
    u8 pad0000[0xe0];
};

struct Effect {
    u8 nFlags;                   /* 0x0000 */
    u8 pad0001[3];
    struct Anim anim;            /* 0x0004 */
    u8 blkChannels;              /* 0x00e4 */
    u8 pad00e5[0x27];
    int nSpare10c;               /* 0x010c */
    int nSpare110;               /* 0x0110 */
    int nArmA;                   /* 0x0114 */
    int nArmB;                   /* 0x0118 */
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
};

/* One entry of the arm table, one per arm count. */
struct ArmEntry {
    int nA;                      /* 0x0000 */
    int nB;                      /* 0x0004 */
};

extern char data_ov022_020b2c34[];
extern char data_ov022_020b2c44[];

extern void func_0202a634(struct Anim *pAnim, char *pszDescriptor, int nA,
                          int nB);
extern void func_0202accc(struct Anim *pAnim, int nChannel, u8 *pBlk,
                          int nGroup);
extern void OS_SPrintf(char *pBuf, const char *pszFmt);
extern struct ArmEntry *func_0201ef9c(char *pszPath, int nHeap);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern int func_020358f4(int nId, int nWhat);

void func_ov022_02093f94(struct Effect *pEffect, int nCount,
                         struct Actor *pActor)
{
    char szPath[0x80];
    struct ArmEntry *pTable;
    /* volatile only to pin the two reads in this order: without it the
     * compiler swaps them and derives the destination offset downward. */
    volatile struct ArmEntry *pEntry;
    int nArmA;
    int nArmB;

    if (nCount <= 0) {
        return;
    }
    func_0202a634(&pEffect->anim, data_ov022_020b2c34, 1, 5);
    func_0202accc(&pEffect->anim, 0, &pEffect->blkChannels, 0);
    func_0202accc(&pEffect->anim, 2, &pEffect->blkChannels, 0);
    func_0202accc(&pEffect->anim, 3, &pEffect->blkChannels, 0);
    func_0202accc(&pEffect->anim, 1, &pEffect->blkChannels, 0);
    OS_SPrintf(szPath, data_ov022_020b2c44);
    pTable = func_0201ef9c(szPath, 6);
    if (nCount > 9) {
        nCount = 9;
    }
    pEntry = (volatile struct ArmEntry *)&pTable[nCount - 1];
    nArmA = pEntry->nA;
    nArmB = pEntry->nB;
    pEffect->nArmA = nArmA;
    pEffect->nArmB = nArmB;
    NNSi_FndFreeFromDefaultHeap(pTable);
    pEffect->nFlags |= 1;
    pEffect->nSpare10c = 0;
    pEffect->nSpare110 = 0;
    if (func_020358f4(pActor->nId, 0x29) != 0) {
        pEffect->nFlags |= 4;
    }
    if (func_020358f4(pActor->nId, 0x2a) != 0) {
        pEffect->nFlags |= 8;
    }
}
