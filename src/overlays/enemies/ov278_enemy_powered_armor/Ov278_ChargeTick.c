/* Charge tick of the ov278 mount. The target comes from 020cab14 (+8); without one the tick waits.
 * With both riders busy the mount turns towards the target (+0x10 heading), its +0x18 step is the
 * cross of the up axis with that direction scaled by the +0x30 side (x 1/8), the +0x3a8 part drops
 * bit 1 and when the +0x2c run time is out the actor requests move 0xb. With a free rider the +0x24
 * timer runs down instead and at its end the actor requests move 9. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct PartFlags { unsigned int lo : 8; };

extern int Ov107_FindNearestObject(int owner, int a);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, void *out);
extern void ScaleVec3Fx12(int scale, void *v, void *out);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const VecFx32 data_02042264;

void Ov278_ChargeTick(int *node)
{
    int *state = (int *)node[1];
    int front = *(int *)(*state + 0x3b4);
    int rear = *(int *)(*state + 0x3b8);
    int frontFree = (*(u16 *)(front + 0x100 + 0xac) & 2) ? 0 : 1;
    int rearFree = (*(u16 *)(rear + 0x100 + 0xac) & 2) ? 0 : 1;
    int target;
    VecFx32 d;

    target = Ov107_FindNearestObject(*state, 0);
    state[2] = target;
    if (target == 0) {
        return;
    }
    if (frontFree == 0 && rearFree == 0) {
        VEC_Subtract((void *)(target + 0x74), (void *)(*state + 0x74), &d);
        d.y = 0;
        VEC_Normalize(&d, &d);
        state[4] = FX_Atan2(d.x, d.z);
        VEC_CrossProduct(&data_02042264, &d, state + 6);
        ScaleVec3Fx12(state[0xc] << 9, state + 6, state + 6);
        ((struct PartFlags *)(*(int *)(*state + 0x3a8) + 8))->lo &= ~2;
        state[0xb] -= *(int *)(node[0] + 0x2c);
        if (state[0xb] > 0) {
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 0xb;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
    } else {
        state[9] -= *(int *)(node[0] + 0x2c);
        if (state[9] >= 0) {
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 9;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
