/* c634 handler: run the guard Ov225_MeasureTargetGap; if <0, dispatch null. Compute the aim
 * angle obj[0x16] = atan2(dir), where dir = VEC_Subtract(obj+0x38, obj[2]). If the target's
 * busy flag (*obj->f0+0x384 +0xad) is clear: try Ov225_ChooseMove; on failure dispatch
 * null, otherwise latch owner+0x1c7=2 and dispatch null. If the flag is set, hand the angle
 * to Ov225_Steer. */

#include "nitro/fx_types.h"

extern int Ov225_MeasureTargetGap(int self, int a);
extern void SetIndexedSlot(int self, int index, void *cb);
extern void VEC_Subtract(int *a, int *b, VecFx32 *out);
extern fx16 FX_Atan2(int dx, int dz);
extern int Ov225_ChooseMove(int self, int r);
extern void Ov225_Steer(int self, int arg);
void Ov225_GuardedAimOrHandoff(int self) {
    int *obj = *(int **)(self + 4);
    VecFx32 buf;
    int r = Ov225_MeasureTargetGap(self, 0);
    if (r < 0) {
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    VEC_Subtract(obj + 0xe, (int *)obj[2], &buf);
    obj[0x16] = FX_Atan2(buf.x, buf.z);
    if (*(unsigned char *)(*(int *)(*obj + 0x384) + 0xad) == 0) {
        if (Ov225_ChooseMove(self, r) != 0) {
            SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        *(char *)(*obj + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    Ov225_Steer(self, obj[0x16]);
}
