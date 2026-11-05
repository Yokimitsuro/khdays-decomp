/* Per-frame update of the ov037 enemy (x4: ov037/055/075/092). In mode 0x2f the local player's
 * own instance samples the target handle into the rig's +0x118 slot; out of that mode a live
 * handle (1) releases the shared effect and is cleared. Then the sub-object step runs with the
 * current tick; at exactly 0x36000 on the +0x7b0 timer in mode 0x30 the enemy tells 0xcf and,
 * when idle and not flagged 0x10000, arms +0x47a/+0x47b; finally, while the emitter at +0x22f8
 * reports activity on an idle session, bit 49 of the +0x464 flags is raised. */

#include "nitro/types.h"
#include "game/engine.h"

extern int func_ov022_02083f0c(void);
extern int Ov022_GetGlobal34(void);
extern void Ov002_StoreVAndToggleBit25(int a, int b, int c);
extern int Ov022_FollowGroundRumble(char *self);
extern void Ov056_CallSubObjThenAdvance(char *self, int tick);
extern void Ov022_PlayEntityVoice(char *self, int nSeqArc, int nSeq);
extern int Ov022_IsState9Or6WithFlag200(char *emitter);
extern void func_ov022_020ad588(char *self);

void Ov056_UpdateTargetAndTimers(char *self)
{
    char *rig = self + 0x2c + 0x2c00;

    if (*(int *)(self + 0x6bc) != 0x2f) {
        if (*(int *)(rig + 0x118) == 1) {
            Ov002_StoreVAndToggleBit25(func_ov022_02083f0c(), 0, 0);
            *(int *)(rig + 0x118) = 0;
        }
    } else {
        if (*(u8 *)(self + 8) == Session_GetLocalPlayerIndex()) {
            *(int *)(rig + 0x118) = Ov022_FollowGroundRumble(self);
        }
    }
    Ov056_CallSubObjThenAdvance(self, Ov022_GetGlobal34());
    switch (*(int *)(self + 0x6bc)) {
    case 0x30:
        if (*(int *)(self + 0x7b0) == 0x36000) {
            Ov022_PlayEntityVoice(self, 0xcf, 0);
            if (Session_GetLocalPlayerIndex() == 0 && (int)(*(long long *)self & 0x10000) == 0) {
                *(u8 *)(self + 0x47a) = 3;
                *(u8 *)(self + 0x47b) = 1;
            }
        }
        break;
    }
    if (Ov022_IsState9Or6WithFlag200(self + 0x2f8 + 0x2000) != 0 && Session_GetLocalPlayerIndex() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x2000000000000ULL;
    }
    func_ov022_020ad588(self);
}
