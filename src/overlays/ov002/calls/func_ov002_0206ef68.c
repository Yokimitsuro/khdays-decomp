/* Claim a handle slot for the event id and mark it pending.
 *
 * Ghidra models the object as Ov002EventContext. Its six tables are really two
 * identical 0x120-byte banks starting at +0xc, which is what the original shows:
 * it holds the selected bank in a register and reaches the flags at +0x100
 * inside it. Bit 12 of the id picks the bank and is cleared to index the flags.
 */

typedef struct {
    int aHandlers[0x20];                /* +0x000 */
    int aSlots[0x20];                   /* +0x080 */
    unsigned char aFlags[0x20];         /* +0x100 */
} Ov002EventBank;                       /* 0x120 */

typedef struct {
    short nVersion;                     /* +0x000 */
    short aHandles[4];                  /* +0x002 */
    unsigned char nCount;               /* +0x00a */
    signed char nCurrent;               /* +0x00b */
    Ov002EventBank aBanks[2];           /* +0x00c */
} Ov002EventContext;                    /* 0x24c */

extern Ov002EventContext *data_ov002_0207fa04;

void func_ov002_0206ef68(int nId)
{
    Ov002EventContext *pContext;
    Ov002EventBank *pBank;
    int i;

    pContext = data_ov002_0207fa04;

    if ((nId & 0x1000) != 0) {
        pBank = &pContext->aBanks[1];
    } else {
        pBank = &pContext->aBanks[0];
    }

    for (i = 0; i < 4; i++) {
        if (pContext->aHandles[i] == -1 || nId == pContext->aHandles[i]) {
            pContext->aHandles[i] = (short)nId;
            break;
        }
    }

    pBank->aFlags[nId & ~0x1000] |= 1;
}
