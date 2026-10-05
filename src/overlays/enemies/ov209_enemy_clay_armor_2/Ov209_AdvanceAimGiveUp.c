/*
 * Ov209_AdvanceAimGiveUp -- x3 (ov208/209/268). AI-state tick: advance an aim and give up when spent.
 * state[0x18] = owner_delta*30/20; state[0xd] = atan2(state[0x15], state[0x17]); ease
 * state[0x16] -= (delta*30<<8 + 0x800)>>12 (a Q12 step). Copy state[0x15..0x17] down to state[5..7]
 * (field-to-field). Once state[0x16] goes negative, mark *state+0x1c7 = 0xb.
 */

#include "nitro/fx_types.h"

struct S208 { char pad[0x14]; VecFx32 a; char pad2[0x34]; VecFx32 b; };
extern fx16 FX_Atan2(int x, int z);

void Ov209_AdvanceAimGiveUp(int *self) {
    int *state = (int *)self[1];

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 20;
    state[0xd] = FX_Atan2(state[0x15], state[0x17]);
    state[0x16] -= (int)((((long long)(*(int *)(*self + 0x2c) * 0x1e) << 8) + 0x800) >> 12);
    ((struct S208 *)state)->a = ((struct S208 *)state)->b;
    if (state[0x16] < 0) {
        *(char *)(*state + 0x1c7) = 0xb;
    }
}
