/* Face the target and start the wind-up: if there is no target, drop straight to action 2.
 * Otherwise play animation 0xc, take the delta from the target's position to ours, turn it
 * into a heading with FX_Atan2(dx, dz), latch that as both the current and the goal heading,
 * clear the travel accumulator, fire the canned 4-byte event, and set 0x40 in the hw60 high
 * byte before continuing.
 *
 * The event template is declared as a STRUCT-TYPED GLOBAL and copied with a plain struct
 * assignment. That is what emits the two halfword loads before the two stores, in descending
 * address order, as the ROM does; casting an `unsigned short[]` global to the struct type
 * instead gives the ascending order and four differing instructions.
 *
 * One of three byte-identical siblings (ov114/ov244/ov277). */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct { unsigned short a, b; } Ov277Pair;

extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(void *node, int idx, void *cb);
extern void Ov277_AiSwingRecover(void);
extern Ov277Pair data_ov277_020d373c;

void Ov277_FaceTargetAndWindUp(int *node) {
    int *state = (int *)node[1];
    Ov277Pair buf;
    VecFx32 d;
    void (*fn)(int, void *, int);
    int v;

    if (state[4] == 0) {
        *(char *)(state[0] + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    Ov107_PostTagUpdate((Actor *)state[0], 0xc, 0);
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[1], &d);
    v = FX_Atan2(d.x, d.z);
    state[6] = v;
    state[5] = v;
    state[0x11] = 0;
    buf = data_ov277_020d373c;
    fn = *(void (**)(int, void *, int))(state[0] + 0x24);
    if (fn != 0) {
        fn(state[0], &buf, 4);
    }
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }
    SetIndexedSlot(node, *(signed char *)((int)node + 0x20), Ov277_AiSwingRecover);
}
