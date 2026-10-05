/* Choose a waypoint from the actor's +0x434 route: the nearest (`nearest` set) or the farthest
 * point from the +8 track is copied to +0x18 and +0x6c becomes the index after it (modulo the
 * +0x454 count). With `outHeading` the heading from that point towards route point +0x6c is
 * stored there. Returns 0 for an empty route, else 1. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern VecFx32 *List_First(void *list);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);
extern fx16 FX_Atan2(int x, int z);

int Ov254_ChooseWaypoint(int *state, int nearest, int *outHeading)
{
    VecFx32 d;
    VecFx32 *p;
    int best = -1;
    int len;
    int i;

    if (*(int *)(*state + 0x454) > 0) {
    p = List_First((void *)(*state + 0x434));
    i = 0;
    if (p != 0) {
    while (p != 0) {
        VEC_Subtract(p, (void *)state[2], &d);
        d.y = 0;
        len = VEC_Mag(&d);
        if (best < 0 || (nearest != 0 && best > len) || (nearest == 0 && best < len)) {
            best = len;
            *(VecFx32 *)(state + 6) = *p;
            state[0x1b] = (i + 1) % *(int *)(*state + 0x454);
        }
        p = (VecFx32 *)List_Next((void *)(*state + 0x434));
        i++;
    }
    }
    if (outHeading != 0) {
        for (p = List_First((void *)(*state + 0x434)), i = 0; p != 0; p = (VecFx32 *)List_Next((void *)(*state + 0x434)), i++) {
            if (i == state[0x1b]) {
                VEC_Subtract(p, state + 6, &d);
                *outHeading = FX_Atan2(d.x, d.z);
                break;
            }
        }
    }
    return 1;
    }
    return 0;
}
