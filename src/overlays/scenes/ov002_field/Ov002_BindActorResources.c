/*
 * Ov002_BindActorResources - point an actor at its model and animation files.
 *
 * Records the slot and kind on the actor, nudges the animation id by 0x50 for
 * the kinds whose variant does not match the expected one, then registers the
 * sequence, resets the element list and the node flags, and finally loads the
 * one file this kind and variant need. Kind 0xe loads a fixed resource by name
 * instead; the rest select a file index of 0 or 1 and load it out of the same
 * packed archive the sequence came from.
 *
 * THUMB. The archive key is packed once into nBase - the top bit, the bank
 * rounded up and shifted, and later the low nine bits of whichever id is being
 * fetched.
 *
 * Three shapes the ROM pins down. The kind groups are ordered with the
 * variant-3 group first in BOTH switches, which also fixes the jump table. The
 * sentinel is assigned after the flag, so mwcc derives -1 by subtracting nine
 * from the 8 it just used. And the two variant tests are written as explicit
 * if/else, not ternaries: a ternary is canonicalised to the opposite branch
 * orientation and no spelling of the condition recovers it.
 */

#include "game/archive.h"

extern void RegisterSeqAndInit(unsigned short *pNode, unsigned int nKey, int nMode,
                          int nHeap);
extern void NNS_G3dMdlSetMdlPolygonIDAll(int nList, int nMask);
extern void SceneNode_SetFlag40(unsigned short *pNode, int nFlag);
extern void Widget_SetTagWord(int nNode, int nValue);
extern unsigned int Archive_LoadFile(unsigned int nKey, int nHeap);
extern void Resource_BindFileToSlot(unsigned int *pSlot, int nNode, unsigned int *pFile,
                          int nHeap);

extern char gOv002XionWMotPackPath[];   /* the fixed resource kind 0xe loads */

void Ov002_BindActorResources(unsigned char *pActor, int nBank, int nSlot,
                         int nKind, unsigned int nAnimId, int nVariant)
{
    unsigned int nBase;
    int nFile;

    pActor[2] = (unsigned char)nSlot;
    pActor[3] = (unsigned char)nKind;

    switch (nKind) {
    case 4:
    case 9:
    case 0xf:
        if (nVariant != 3) {
            nAnimId = nAnimId + 0x50;
        }
        break;
    case 2:
    case 0x13:
        if (nVariant != 1) {
            nAnimId = nAnimId + 0x50;
        }
        break;
    }

    nBase = ARCHIVE_HANDLE(nBank, 0);
    RegisterSeqAndInit((unsigned short *)(pActor + 4), nBase | (nAnimId & 0x1ff), 1,
                  pActor[2] + 7);
    NNS_G3dMdlSetMdlPolygonIDAll(*(int *)(pActor + 0x7c), 0x3f);
    SceneNode_SetFlag40((unsigned short *)(pActor + 4), 1);
    Widget_SetTagWord((int)(pActor + 4), 0x7fff);

    pActor[0] = pActor[0] | 8;
    nFile = -1;
    switch (nKind) {
    case 0:
    case 5:
    case 6:
    case 0xb:
    case 0x10:
        nFile = 0;
        break;
    case 4:
    case 9:
    case 0xf:
        if (nVariant == 3) {
            nFile = 0;
        } else {
            nFile = 1;
        }
        break;
    case 2:
    case 0x13:
        if (nVariant == 1) {
            nFile = 0;
        } else {
            nFile = 1;
        }
        break;
    case 0xe:
        *(unsigned int *)(pActor + 0x160) =
            Archive_LoadFile((unsigned int)gOv002XionWMotPackPath, pActor[2] + 7);
        Resource_BindFileToSlot((unsigned int *)(pActor + 0x13c), (int)(pActor + 4),
                      *(unsigned int **)(pActor + 0x160), pActor[2] + 7);
        pActor[0] = pActor[0] | 4;
        break;
    }

    if (nFile >= 0) {
        *(unsigned int *)(pActor + 0x160) =
            Archive_LoadFile(nBase | ((nFile + 0xdc) & 0x1ff), nSlot + 7);
        Resource_BindFileToSlot((unsigned int *)(pActor + 0x13c), (int)(pActor + 4),
                      *(unsigned int **)(pActor + 0x160), pActor[2] + 7);
        pActor[0] = pActor[0] | 4;
    }
    pActor[1] = (unsigned char)nVariant;
}
