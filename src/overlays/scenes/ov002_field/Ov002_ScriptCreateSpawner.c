
#include "nitro/fx_types.h"

extern int ScriptVm_ReadOperandInt(int pCtx, unsigned short *pOperand);
extern int ScriptVm_ReadOperandFx32(int pCtx, unsigned short *pOperand);
/* The setup makes the spawner, stamps its place and four values into the object it makes, and
 * starts its trigger. */
extern void Ov002_CreateSpawner(int nGroup, int nRegion, int nMask, int nMode,
                                VecFx32 *pAt, int fxSpread, int nTag,
                                int fxScale, int fxKeepNear, VecFx32 *pTriggerAt,
                                int fxTriggerRadius, int bShown);

/* Script command 2.32: make a field spawner and start it.
 *
 * Sixteen operands feed the setup (Ov002_CreateSpawner): its group of the enemy table, the region
 * (aSources[], Ov107_Region_New) it and its enemies belong to, a mask and a mode; the fifth says
 * whether its group's node is shown and goes in last as a boolean. Three fixed-point operands give
 * the spawner's place; then how far its enemies are placed around it (+0x110,
 * Ov107_Spawner_PlaceActors), a tag, a scale (+0x118) and the distance within which a player keeps
 * them (+0x114: none near, they are called back); three more give the centre of its trigger
 * sphere and the last its radius (0: a restart task instead). Always returns one.
 */
int Ov002_ScriptCreateSpawner(int pCtx, unsigned short *pArgs)
{
    VecFx32 vAt;
    VecFx32 vTriggerAt;
    int nGroup;
    int nRegion;
    int nMask;
    int nMode;
    int nShown;
    int fxSpread;
    int nTag;
    int fxScale;
    int fxKeepNear;
    int fxTriggerRadius;

    nGroup = ScriptVm_ReadOperandInt(pCtx, pArgs);
    nRegion = ScriptVm_ReadOperandInt(pCtx, pArgs + 4);
    nMask = ScriptVm_ReadOperandInt(pCtx, pArgs + 8);
    nMode = ScriptVm_ReadOperandInt(pCtx, pArgs + 0xc);
    nShown = ScriptVm_ReadOperandInt(pCtx, pArgs + 0x10);
    vAt.x = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x14);
    vAt.y = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x18);
    vAt.z = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x1c);
    fxSpread = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x20);
    nTag = ScriptVm_ReadOperandInt(pCtx, pArgs + 0x24);
    fxScale = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x28);
    fxKeepNear = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x2c);
    vTriggerAt.x = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x30);
    vTriggerAt.y = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x34);
    vTriggerAt.z = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x38);
    fxTriggerRadius = ScriptVm_ReadOperandFx32(pCtx, pArgs + 0x3c);

    Ov002_CreateSpawner(nGroup, nRegion, nMask, nMode, &vAt, fxSpread,
                        nTag, fxScale, fxKeepNear, &vTriggerAt, fxTriggerRadius,
                        nShown != 0);
    return 1;
}
