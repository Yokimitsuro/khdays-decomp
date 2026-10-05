/* Waits out 0x6ee of scene time, accumulating the frame delta and returning early until it is
 * reached. Then it re-acquires the target and, if there is one, aims the facing at it with the
 * horizontal angle from the actor to the target. Finally it clears bits 6 and 7 of the high byte of
 * wFlags60, stops the actor's motion, resets the elapsed counter and installs the next state. */

#include "nitro/types.h"
#include "game/ai_task.h"

typedef struct {
    int nX;
    int nY;
    int nZ;
} VecFx32;

struct Flags60 {
    u16 lo : 8;
    u16 hi : 8;
};

struct State {
    char *pActor;
    int nAngle04;
    int nAngleTarget08;
    char pad0c[4];
    VecFx32 *pPos10;
    char pad14[4];
    void *pTarget;      /* 0x18 */
    char pad1c[0xc];
    int nElapsed28;
};

struct Node {
    AI_TASK_FIELDS(struct State)
};

extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *ab);
extern short FX_Atan2(int x, int z);
extern void *Ov107_FindNearestObject(char *actor, int mode);
extern void Ov107_PostTagUpdate(char *actor, int a, int b);
extern void SetIndexedSlot(struct Node *node, int slot, void *next);

extern void Ov286_AccumulateTimer28ThenAdvanceAt400(void);

void Ov286_Wait_Tick(struct Node *node)
{
    struct State *st;
    VecFx32 vToTarget;
    void *pTarget;
    int nElapsed;
    int nAngle;

    st = node->pState;
    nElapsed = st->nElapsed28 + *(int *)((char *)node->pList + 0x2c);
    st->nElapsed28 = nElapsed;
    if (nElapsed < 0x6ee) {
        return;
    }

    pTarget = Ov107_FindNearestObject(st->pActor, 0);
    st->pTarget = pTarget;
    if (pTarget != 0) {
        VEC_Subtract((VecFx32 *)((char *)pTarget + 0x74), st->pPos10, &vToTarget);
        nAngle = FX_Atan2(vToTarget.nX, vToTarget.nZ);
        st->nAngleTarget08 = nAngle;
        st->nAngle04 = nAngle;
    }

    ((struct Flags60 *)(st->pActor + 0x60))->hi =
        ((struct Flags60 *)(st->pActor + 0x60))->hi & ~0xc0;
    Ov107_PostTagUpdate(st->pActor, 0, 0);
    st->nElapsed28 = 0;
    SetIndexedSlot(node, node->slot, (void *)Ov286_AccumulateTimer28ThenAdvanceAt400);
}
