
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern char *Ov002_ClaimPoolEntry(char *pClass, int nSlot);
extern int Ov002_PlaceElementNode(void *pObj, int nNode, void *pOut,
                                int nUnused, int nKind, int nParamA,
                                int nParamB, int nParamC,
                                int nAngle, int nFlag);
extern void Ov002_BuildSpawnPosition(VecFx32 *pOut, VecFx32 *pPos, int *pIn);
extern void Ov002_PushBucketNode(int nRoom, char *pPiece);
extern void Ov002_DoneTick(void);

/* Bring one piece of a class up and put it on the board.
 *
 * The piece takes its placement from the class it came from, is moved to the
 * point the caller gives and is handed the class's own per-frame hook.  A
 * class whose kind is neither 0 nor 3 also gets its extra node switched on.
 * The finished piece is registered in the caller's bucket and handed back.
 */
char *Ov002_SpawnPieceElement(char *pClass, u16 wSlot, u16 wBucket,
                          u16 wStateField, u8 bStateWidth, VecFx32 *pPos,
                          s16 nAngle)
{
    VecFx32 vOut;
    int aSetup[5];
    char *pPiece;

    pPiece = Ov002_ClaimPoolEntry(pClass, wSlot);
    Ov002_PlaceElementNode(pPiece, (int)(pPiece + 0x1c), aSetup, wSlot,
                        *(s8 *)(pClass + 0x78),
                        *(int *)(pClass + 0x6c),
                        *(int *)(pClass + 0x70),
                        *(int *)(pClass + 0x74),
                        nAngle, 1);
    Ov002_BuildSpawnPosition(&vOut, pPos, aSetup);
    *(int *)(pPiece + 0x19c) = 0x1000;
    Actor_SetVecAndSyncChild(pPiece + 0x28, pPos);

    *(s16 *)(pPiece + 0x18) = nAngle;
    *(u8 *)(pPiece + 0x10) = (u8)wBucket;
    *(void **)(pPiece + 0x0c) = (void *)Ov002_DoneTick;
    *(s16 *)(pPiece + 0x14) = (s16)wStateField;
    *(u8 *)(pPiece + 0x16) = bStateWidth;
    *(u8 *)(pPiece + 0x17) = 0;
    *(s8 *)(pPiece + 0x1a0) = *(s8 *)(pClass + 0x79);

    if (*(s8 *)(pClass + 0x78) != 3 && *(s8 *)(pClass + 0x78) != 0) {
        Actor_SetBindingByte(pPiece + 0x138, 1, 3);
    }

    *(s16 *)(pPiece + 0x1a2) = 0;
    Ov002_PushBucketNode(wBucket, pPiece);
    return pPiece;
}
