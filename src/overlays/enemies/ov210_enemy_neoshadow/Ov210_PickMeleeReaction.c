/*
 * Ov210_PickMeleeReaction -- x3 (ov210/211/282). AI-state tick: pick a melee reaction toward the target.
 * state = *(int**)(self+4). With a target (state[8]!=0): dir = target(+0x190) - *state(+0xb0);
 * forward = transform(*state+0xa0, data_02042258). dot = dir . forward. Read facing bit0 at
 * *state+0x17a. Four-way pick, each leaf spelled out (the ROM shares no tail):
 *   dot > 0 (in front):  bit0 -> attack 2, else attack 4; heading = atan2(dir.x, dir.z)
 *   dot <= 0 (behind):   bit0 -> attack 3, else attack 5; heading = atan2(dir.x, dir.z) + 0x3244 (pi)
 * state[9]=state[10]=heading, hand off to 020d10e8. No target (state[8]==0, out-of-line tail): fire
 * attack 2 and hand off to 020d10e8.
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

struct b17a { unsigned char b0 : 1; };
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  VEC_DotProduct(void *a, void *b);
extern fx16  FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void Ov210_AiLandPickNext(void);
extern int  data_02042258;

void Ov210_PickMeleeReaction(int self) {
    int *state = *(int **)(self + 4);
    VecFx32 w;
    VecFx32 v;
    int a;

    if (state[8] != 0) {
        VEC_Subtract((void *)(state[8] + 0x190), (void *)(*state + 0xb0), &v);
        Vec3TransformViaTempMtx(&w, (void *)(*state + 0xa0), &data_02042258);
        if (VEC_DotProduct(&v, &w) > 0) {
            if (((struct b17a *)(*state + 0x17a))->b0) {
                Ov107_PostTagUpdate((Actor *)(*state), 2, 0);
                a = FX_Atan2(v.x, v.z);
                state[10] = a;
                state[9] = a;
                SetIndexedSlot(self, *(signed char *)(self + 0x20), (int)&Ov210_AiLandPickNext);
                return;
            }
            Ov107_PostTagUpdate((Actor *)(*state), 4, 0);
            a = FX_Atan2(v.x, v.z);
            state[10] = a;
            state[9] = a;
            SetIndexedSlot(self, *(signed char *)(self + 0x20), (int)&Ov210_AiLandPickNext);
            return;
        }
        if (((struct b17a *)(*state + 0x17a))->b0) {
            Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
            a = FX_Atan2(v.x, v.z) + 0x3244;
            state[10] = a;
            state[9] = a;
            SetIndexedSlot(self, *(signed char *)(self + 0x20), (int)&Ov210_AiLandPickNext);
            return;
        }
        Ov107_PostTagUpdate((Actor *)(*state), 5, 0);
        a = FX_Atan2(v.x, v.z) + 0x3244;
        state[10] = a;
        state[9] = a;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), (int)&Ov210_AiLandPickNext);
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 2, 0);
    SetIndexedSlot(self, *(signed char *)(self + 0x20), (int)&Ov210_AiLandPickNext);
}
