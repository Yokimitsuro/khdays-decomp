#include "nitro/fx_types.h"

extern int ScriptVm_ReadOperandInt(int ctx, void *arg);
extern int ByteCode_ResolveOperand(int ctx, void *arg);
extern char *ScriptVm_ResolveOperand(int ctx, void *arg);
extern int ScriptVm_ResolveActorIndex(int ctx, int arg);
extern char *ArrayEntryPtrD0(int index);
extern void EntityMgr_ProbeGround(int id, int a, void *out);
extern int FX_Atan2Idx(int y, int x);
extern int Ov023_TurnActorToward(int ctx, int id, int angle);

/* Script command: turns the entity to face the point named by operand 1 -- either another
 * entity's position or a resolved world point. */
int Ov023_Cmd_FaceEntityTowards(int ctx, char *args) {
    int entity = ScriptVm_ReadOperandInt(ctx, args);
    char *op = ScriptVm_ResolveOperand(ctx, args + 8);
    int id = ScriptVm_ResolveActorIndex(ctx, entity);
    VecFx32 here;
    VecFx32 target;
    unsigned short angle;
    if (*(short *)op == 1) {
        target = *(VecFx32 *)(ArrayEntryPtrD0((unsigned short)ScriptVm_ResolveActorIndex(ctx,
                     ScriptVm_ReadOperandInt(ctx, op))) + 0xa8);
    } else if (*(short *)op == 2) {
        EntityMgr_ProbeGround((unsigned short)id, ByteCode_ResolveOperand(ctx, op), &target);
    } else {
        return 1;
    }
    here = *(VecFx32 *)(ArrayEntryPtrD0((unsigned short)id) + 0xa8);
    here.x = target.x - here.x;
    here.z = target.z - here.z;
    angle = (unsigned short)(0x13fff - FX_Atan2Idx(here.z, here.x));
    return Ov023_TurnActorToward(ctx, id, angle);
}
