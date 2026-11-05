
/* One object slot, 0x18 bytes. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov002ObjectSlot {
    void *pObject;                      /* +0x00 */
    VecFx32 vAt;                      /* +0x04 */
    int fxRadius;                       /* +0x10: the trigger sphere's radius */
    u8 bEntryIndex;                     /* +0x14 */
    char pad15[3];
} Ov002ObjectSlot;

typedef struct Ov002ObjectContext {
    char pad00[0x44];
    Ov002ObjectSlot *pSlots;            /* +0x44 */
} Ov002ObjectContext;

/* The block Ov107_CreateTriggerSphere takes: the centre and the radius. */
typedef struct Ov002TriggerSphere {
    VecFx32 vAt;                      /* +0x00 */
    int fxRadius;                       /* +0x0c */
} Ov002TriggerSphere;

extern Ov002ObjectContext *data_ov002_0207fa14;

extern int Ov107_CreateRestartTask(void);
extern int Ov107_CreateTriggerSphere(Ov002TriggerSphere *pAt);
extern void Ov107_Spawner_SetMoveAnim(void *pObject, int nAnim, int nFlag);
extern void Ov002_SetKeyNodeVisible(int nKey, int nParam, int nFlag);

/* Start a spawner's trigger and record where it is.
 *
 * A radius of zero makes a restart task; any other radius a trigger sphere of that radius around
 * the given centre, handed the centre and the radius together in a block on the stack. Either way
 * the task goes to the spawner's object. The centre is then copied into the slot when the caller
 * gave one, the radius and the group are stamped in, and the group's node is shown or not.
 */
void Ov002_StartSpawnerTrigger(int nIndex, int nGroup, int fxRadius, VecFx32 *pCentre,
                         int bShown)
{
    Ov002ObjectContext *pCtx;
    Ov002TriggerSphere at;
    int nTask;

    pCtx = data_ov002_0207fa14;
    if (fxRadius == 0) {
        nTask = Ov107_CreateRestartTask();
        Ov107_Spawner_SetMoveAnim(pCtx->pSlots[nIndex].pObject, nTask, 1);
    } else {
        at.vAt.x = pCentre->x;
        at.vAt.y = pCentre->y;
        at.vAt.z = pCentre->z;
        at.fxRadius = fxRadius;
        nTask = Ov107_CreateTriggerSphere(&at);
        Ov107_Spawner_SetMoveAnim(pCtx->pSlots[nIndex].pObject, nTask, 1);
    }

    if (pCentre != 0) {
        pCtx->pSlots[nIndex].vAt = *pCentre;
    }
    pCtx->pSlots[nIndex].fxRadius = fxRadius;
    pCtx->pSlots[nIndex].bEntryIndex = (u8)nGroup;
    Ov002_SetKeyNodeVisible(nGroup, bShown, -1);
}
