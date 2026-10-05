/* Attack entry of the ov219 enemy: plays animation 6, starts sub-animation 0, fires reaction
 * 0x136 mode 6 at the +8 position; coming from sub-state 3 with the +0x21a stamina spent the
 * +0x388 item's +8 byte gets bit 1, and with a +0x40 target the +0xc/+0x10 yaw turns towards it
 * (from the actor's +0xb0 point to the target's +0x190 point). The target is cleared and the
 * tick hands off to the attack tick. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

struct b8 { unsigned f : 8; };

extern void Ov219_startAnim(int actor, int anim);
extern void Ov107_BuildAndSendUpdate(int actor, int a, int id, void *at);
extern void VEC_Subtract(void *a, void *b, void *d);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov219_AttackTick(int *node);

void Ov219_BeginAttack(int *node)
{
    int *state = (int *)node[1];
    VecFx32 dir;
    int actor;

    Ov107_PostTagUpdate((Actor *)(*state), 6, 0);
    Ov219_startAnim(*state, 0);
    Ov107_BuildAndSendUpdate(*state, 0x136, 6, (void *)state[2]);
    actor = *state;
    if (*(signed char *)(actor + 0x1c6) == 3) {
        if (*(s16 *)(actor + 0x21a) == 0) {
            ((struct b8 *)(*(int *)(actor + 0x388) + 8))->f |= 2;
        }
        if (state[0x10] != 0) {
            VEC_Subtract((void *)(state[0x10] + 0x190), (void *)(*state + 0xb0), &dir);
            state[3] = state[4] = FX_Atan2(dir.x, dir.z);
        }
    }
    state[0x10] = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov219_AttackTick);
}
