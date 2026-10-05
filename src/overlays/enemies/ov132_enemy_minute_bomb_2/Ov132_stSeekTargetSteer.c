/* AI step: steers toward the nearest target: gives up (action 2) without one or when it is out of
 * reach, otherwise sets the heading and a speed along the facing, and once within 0x1000 posts pose
 * 9 and installs the attack step. */

#include "game/enemy_common.h"

extern void *Ov107_FindNearestObject(void *obj, int a);
extern void SetIndexedSlot(void *node, int idx, void *value);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Normalize(void *v, void *v2);
extern fx16 FX_Atan2(int a, int b);
extern int VEC_DotProduct(void *a, void *b);
extern void ScaleVec3Fx12(int scale, void *vec, void *out);
extern void Ov132_AiStep_QueueAction9OnFlag48Clear(void);

extern short data_0203d210[];

void Ov132_stSeekTargetSteer(int *node)
{
    int vd[3];
    int va[3];
    int *state = (int *)node[1];
    int *obj;
    int dist;
    int angle;
    short *tbl;

    state[2] = (int)Ov107_FindNearestObject((void *)*state, 0);
    if (state[2] == 0) {
        obj = (int *)*state;
        *((signed char *)obj + 0x1c7) = 2;
        SetIndexedSlot(node, (signed char)*((char *)node + 0x20), 0);
        return;
    }

    VEC_Subtract((char *)state[2] + 0x190, (char *)*state + 0xb0, vd);
    vd[1] = 0;

    {
        int *o = (int *)*state;
        int *h = (int *)state[2];
        dist = VEC_Normalize(vd, vd) - (*(int *)((char *)h + 0x80) + *(int *)((char *)o + 0x80));
    }
    state[4] = FX_Atan2(vd[0], vd[2]);

    angle = (int)(((unsigned)(((long long)state[3] * 0x28be60db9391LL + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;

    va[1] = 0;
    tbl = data_0203d210;
    va[0] = tbl[angle * 2];
    va[2] = tbl[angle * 2 + 1];

    {
        int dot = VEC_DotProduct(va, vd);
        if (dot < 0)
            dot = -dot;
        ScaleVec3Fx12((int)(((long long)dot * 0x300 + 0x800) >> 0xc), va, state + 6);
    }

    obj = (int *)*state;
    if (dist >= *(int *)((char *)obj + 0x2d8)) {
        *((signed char *)obj + 0x1c7) = 2;
        SetIndexedSlot(node, (signed char)*((char *)node + 0x20), 0);
        return;
    }
    if (dist > 0x1000)
        return;
    Ov107_PostTagUpdate((Actor *)obj, 9, 0);
    SetIndexedSlot(node, (signed char)*((char *)node + 0x20), Ov132_AiStep_QueueAction9OnFlag48Clear);
}
