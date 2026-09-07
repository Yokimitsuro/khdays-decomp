/* ov022: start a part model loading into a grid entry.
 *
 * Hands the path and the entry's share of the slot budget to the loader, keeps
 * the handle it gets back, remembers the animation block the model will bind
 * to, and marks the entry busy.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct GridEntry {
    u8 nFlags;                   /* 0x00 */
    u8 pad01[2];
    u8 nStage;                   /* 0x03 */
    u8 pad04[0x24];
    u16 *pBlock;                 /* 0x28 */
    int nBase;                   /* 0x2c */
    u16 nHandle;                 /* 0x30 */
    u16 nSize;                   /* 0x32 */
    u8 pad34[4];
};

extern int func_0201ed3c(const char *pPath, int nBase, int nSize);

void func_ov022_020b11e8(struct GridEntry *pEntry, const char *pPath,
                         u16 *pBlock)
{
    int nHandle;

    nHandle = func_0201ed3c(pPath, pEntry->nBase, pEntry->nSize);
    pEntry->pBlock = pBlock;
    pEntry->nHandle = nHandle;
    pEntry->nFlags |= 1;
    pEntry->nStage = 1;
}
