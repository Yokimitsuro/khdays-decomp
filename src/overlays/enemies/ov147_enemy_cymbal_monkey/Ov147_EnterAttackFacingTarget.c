/* Four forms from codegen-cracks.md, all needed:
 *  - hw60 `hi |= 0x80` uses the EXPLICIT extract/reassemble (no lsl#0x10/lsr#0x10 pair);
 *  - hw60 `hi &= ~0xc` uses the BITFIELD (it does have the pair). The two opposite forms
 *    back to back, exactly as in ov119 020ccef4.
 *  - the `&= ~1` at +8 is a BYTE field, so it needs a real bitfield type;
 *  - func_ov107_020c0b90 takes the vec BY VALUE. */

#include "nitro/fx_types.h"

typedef struct { unsigned short lo : 8, hi : 8; } Hw60;
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;

extern void Ov107_BuildAndSendUpdate();
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 v, int flag);
extern int  Ov107_FindNearestObject(int obj, int flag);
extern void VEC_Subtract();
extern fx16  FX_Atan2(int a, int b);
extern void SetIndexedSlot(int self, int index, void *cb);
extern VecFx32 data_02041dc8;
extern void Ov147_ClearMoveTimerAndFire(void);

void Ov147_EnterAttackFacingTarget(int self) {
    int *obj = *(int **)(self + 4);
    int v[3];
    int target;
    unsigned short w;

    w = *(unsigned short *)(*obj + 0x60);
    *(unsigned short *)(*obj + 0x60) =
        (unsigned short)((w & ~0xff00)
                         | (((((unsigned int)w << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10));
    ((Hw60 *)(*obj + 0x60))->hi &= ~0xc;
    *(unsigned short *)(*obj + 0x1ae) |= 1;
    ((Byte8 *)(*(int *)(*obj + 0x38c) + 8))->lo &= ~1;
    Ov107_BuildAndSendUpdate(*obj, 0, 0x48, *obj + 0x74);
    func_ov107_020c0b90(*obj, 2, data_02041dc8, 0);
    *(int *)(*obj + 0x394) = Ov107_FindNearestObject(*obj, 0);
    target = *(int *)(*obj + 0x394);
    if (target != 0) {
        VEC_Subtract(target + 0x74, *obj + 0x74, v);
        obj[0xe] = FX_Atan2(v[0], v[2]);
        obj[0xd] = obj[0xe];
    }
    obj[0x10] = 0;
    *(signed char *)((int)obj + 0x45) = 0;
    SetIndexedSlot(self, *(signed char *)(self + 0x20), &Ov147_ClearMoveTimerAndFire);
}
