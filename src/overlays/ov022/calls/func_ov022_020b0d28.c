/* ov022: draw the voice entry a tag names, at a frame.
 *
 * Nothing happens on a table that was never built, on a negative frame, on a
 * tag the table does not carry, or on a frame past the entry's own length. When
 * all four hold, the entry's bind block is wired to all five channels, every
 * channel is wound to the frame, and the model is submitted under the matrix
 * the caller hands in.
 *
 * The bind loop counts on the same variable the tag count used, and the wind
 * loop on its own. That reuse is load bearing: with two fresh counters the
 * hoisted bind offset and the counter swap registers, and no declaration order
 * of the locals -- all 720 were tried -- puts them back.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define CHANNEL_COUNT 5
#define BIND_STRIDE 0x24
#define TAG_NONE (-1)
#define FLAG_BUILT 1

struct ActionTable {
    u32 nFlags;                  /* 0x0000 */
    u8 pad0004[0x8c];
    u8 anim;                     /* 0x0090 */
    u8 pad0091[0x1f];
    u8 renderObj;                /* 0x00b0 */
    u8 pad00b1[0xe7];
    u8 *pVoiceBinds;             /* 0x0198 */
    u8 pad019c[4];
    int nVoiceCount;             /* 0x01a0 */
    u8 *pVoiceTags;              /* 0x01a4 */
};

extern void func_0202accc(u8 *pAnim, int nChannel, u8 *pBind, int nGroup);
extern int func_0202aef8(u8 *pAnim, int nChannel);
extern void func_01fff774(u8 *pAnim, int nChannel, int nFrame);
extern void func_0201571c(void);
extern void func_01ff9f00(u32 nCmd, const void *pSrc, u32 nWords);
extern void func_020279e0(u8 *pObj);

void func_ov022_020b0d28(struct ActionTable *pTable, int nTag, int nFrame,
                         const void *pMtx)
{
    int nChannel;
    int nEntry;
    int nFound;
    u8 *pTag;
    int nCount;

    if ((pTable->nFlags & FLAG_BUILT) == 0) {
        return;
    }
    if (nFrame < 0) {
        return;
    }
    nCount = pTable->nVoiceCount;
    nFound = TAG_NONE;
    nEntry = 0;
    if (nCount > 0) {
        pTag = pTable->pVoiceTags;
        do {
            if (nTag == *pTag) {
                nFound = nEntry;
                break;
            }
            nEntry++;
            pTag++;
        } while (nEntry < nCount);
    }
    if (nFound == TAG_NONE) {
        return;
    }
    for (nCount = 0; nCount < CHANNEL_COUNT; nCount++) {
        func_0202accc(&pTable->anim, (u16)nCount,
                      &pTable->pVoiceBinds[nFound * BIND_STRIDE], 0);
    }
    if (func_0202aef8(&pTable->anim, 0) < nFrame) {
        return;
    }
    for (nChannel = 0; nChannel < CHANNEL_COUNT; nChannel++) {
        func_01fff774(&pTable->anim, (u16)nChannel, nFrame);
    }
    func_0201571c();
    func_01ff9f00(0x17, pMtx, 12);
    func_020279e0(&pTable->renderObj);
}
