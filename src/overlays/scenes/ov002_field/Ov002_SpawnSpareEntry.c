
#include "nitro/types.h"
#include "nitro/fx_types.h"

extern char *Ov002_ClaimPoolEntry(void *pClass, int nSlot);
extern int Ov002_GetCtxTableByte(int nRoom);
extern unsigned int strlen(const char *s);
extern void strcpy(void *pDst, const void *pSrc);
extern void Ov002_PushBucketNode(int nRoom, char *pEntry);
extern void Ov002_SpareEntryStep(void);

/* Spawn one spare entry of a class.
 *
 * Claims an entry, puts it at the caller's position and takes the two texts:
 * with neither there is nothing to say, with only a line the name is blank.
 * The count comes in signed - a negative one means the entry is held rather
 * than counted - and two flags arm the park handler and the wide slot. The
 * state machine is installed last and the entry is pushed into its bucket.
 */
char *Ov002_SpawnSpareEntry(void *pClass, int nSlot, int nRoom, const VecFx32 *pPos,
                          u16 wStateField, unsigned char bStateWidth,
                          signed char bQueuedWidth, signed char nCount,
                          const char *pName, const char *pLine,
                          int nParamA, int nParamB, int bArm, int bWide)
{
    char *pEntry;

    pEntry = Ov002_ClaimPoolEntry(pClass, nSlot);
    Ov002_GetCtxTableByte(nRoom);

    *(VecFx32 *)(pEntry + 0x1c) = *pPos;

    *(int *)(pEntry + 0x28) = nParamB;
    *(int *)(pEntry + 0x44) = nParamA;

    if (pName == 0 && pLine == 0) {
        *(signed char *)(pEntry + 0x37) = 0;
        *(signed char *)(pEntry + 0x2f) = *(signed char *)(pEntry + 0x37);
    } else {
        if (pName == 0) {
            *(signed char *)(pEntry + 0x2f) = 0;
        } else {
            strlen(pName);
            strcpy(pEntry + 0x2f, pName);
        }
        strlen(pLine);
        strcpy(pEntry + 0x37, pLine);
    }

    *(unsigned char *)(pEntry + 0x2c) = 0;
    *(unsigned char *)(pEntry + 0x3f) = 0;
    *(signed char *)(pEntry + 0x2e) = bQueuedWidth;

    if (nCount < 0) {
        *(signed char *)(pEntry + 0x40) = 0x10;
        *(signed char *)(pEntry + 0x40) |= 1;
    } else {
        *(signed char *)(pEntry + 0x40) = nCount & 0xf;
    }

    if (bArm != 0) {
        *(signed char *)(pEntry + 0x40) |= 0x40;
    }
    if (bWide != 0) {
        *(signed char *)(pEntry + 0x40) |= 0x20;
    }

    *(unsigned char *)(pEntry + 0x2d) = (unsigned char)nSlot;

    *(unsigned char *)(pEntry + 0x10) = (unsigned char)nRoom;
    *(int *)(pEntry + 0x0c) = (int)Ov002_SpareEntryStep;
    *(u16 *)(pEntry + 0x12) |= 8;

    *(u16 *)(pEntry + 0x14) = wStateField;
    *(unsigned char *)(pEntry + 0x16) = bStateWidth;
    *(unsigned char *)(pEntry + 0x17) = *(signed char *)(pEntry + 0x2e);

    Ov002_PushBucketNode(nRoom, pEntry);
    return pEntry;
}
