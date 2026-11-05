
/* The 20 byte placement record the node call reads. Only the first three
 * fields are set here. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int nKind;                      /* +0x00 */
    int nParamB;                    /* +0x04 */
    int nParamA;                    /* +0x08 */
    int nParamC;                    /* +0x0c */
    int nAngle;                     /* +0x10 */
} Ov002PlaceParams;

extern char *Ov002_ClaimPoolEntry(char *pClass, int nSlot);
extern int Actor_ArmWithMessage(int nNode, int nZero, void *pObj,
                         Ov002PlaceParams *pParams, int nFlag);
extern void Actor_SetVecAndSyncChild(char *pNode, VecFx32 *pPos);
extern int Ov002_TakeEntryOfKind1(void);
extern void Ov002_PushBucketNode(int nRoom, char *pElement);
extern void Ov002_Element_PickTick(char *pElement);

/* Spawn one timed element of a class.
 *
 * Claims a pool entry, places its node with a fixed pair of placement
 * parameters, moves it to the requested position and remembers that position
 * and angle. The key, the claimed unit and the slot are stamped, the element
 * starts in state 3, and the per-frame handler is installed before the node
 * goes into its bucket.
 */
void Ov002_SpawnTimedElementAt(char *pClass, int nSlot, int nRoom, VecFx32 *pPos,
                         short nAngle, u16 wStateField,
                         unsigned char bStateWidth, short nKey)
{
    char *pElement;
    Ov002PlaceParams place;
    VecFx32 vPos;

    pElement = Ov002_ClaimPoolEntry(pClass, nSlot);

    place.nParamA = 0x800;
    place.nParamB = 0xb5c;
    place.nKind = 0;
    Actor_ArmWithMessage((int)(pElement + 0x2c), 0, pElement, &place, 1);

    vPos = *pPos;
    Actor_SetVecAndSyncChild(pElement + 0x38, &vPos);

    *(short *)(pElement + 0x18) = nAngle;
    *(VecFx32 *)(pElement + 0x1c) = *pPos;
    *(int *)(pElement + 0x28) = place.nParamA;

    *(u16 *)(pElement + 0x1b6) = nKey;
    *(int *)(pElement + 0x1b0) = 0;

    *(unsigned char *)(pElement + 0x1b9) =
        (unsigned char)Ov002_TakeEntryOfKind1();
    *(unsigned char *)(pElement + 0x1ba) = (unsigned char)nSlot;
    *(unsigned char *)(pElement + 0x1b4) = 3;

    *(unsigned char *)(pElement + 0x10) = (unsigned char)nRoom;
    *(int *)(pElement + 0x0c) = (int)Ov002_Element_PickTick;
    *(u16 *)(pElement + 0x12) |= 8;
    *(u16 *)(pElement + 0x14) = wStateField;
    *(unsigned char *)(pElement + 0x16) = bStateWidth;
    *(unsigned char *)(pElement + 0x17) = 1;

    Ov002_PushBucketNode(nRoom, pElement);
}
