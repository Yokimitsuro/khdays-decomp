/*
 * Ov271_AimLeadTarget -- x3. AI-state tick: aim toward the target and lead it, store the heading.
 * target = acquire(*state, 0) -> state[2]. dir = normalise(target(+0x74) - state[0x13]) -> state[0xf];
 * state[9] = dir * 0x800 (lead offset). Build the lead point state[0xc] = (*state+0xb0) + state[9];
 * state[0xd] = *(*state+0x78) - *(*state+0x80). Then heading = atan2 of (state[0xc] - (*state+0xb0)),
 * stored at *(*state+0x3ac).
 */

#include "nitro/fx_types.h"

extern int  Ov107_FindNearestObject(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *a, void *b);
extern void ScaleVec3Fx12(int scale, void *in, void *out);
extern void VEC_Add(void *a, void *b, void *c);
extern fx16  FX_Atan2(int x, int z);

void Ov271_AimLeadTarget(int *self) {
    int *state = (int *)self[1];
    VecFx32 v;
    int w[3];
    int target = Ov107_FindNearestObject(*state, 0);

    state[2] = target;
    VEC_Subtract((void *)(target + 0x74), (void *)state[0x13], (void *)(state + 0xf));
    VEC_Normalize((void *)(state + 0xf), (void *)(state + 0xf));
    ScaleVec3Fx12(0x800, (void *)(state + 0xf), (void *)(state + 9));
    v = *(VecFx32 *)(*state + 0xb0);
    VEC_Add(&v, (void *)(state + 9), &v);
    *(VecFx32 *)(state + 0xc) = v;
    state[0xd] = *(int *)(*state + 0x78) - *(int *)(*state + 0x80);
    VEC_Subtract((void *)(state + 0xc), (void *)(*state + 0xb0), w);
    *(int *)(*state + 0x3ac) = FX_Atan2(w[0], w[2]);
}
