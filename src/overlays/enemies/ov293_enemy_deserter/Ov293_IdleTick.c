/* Idle tick of the ov293 enemy: the +0x14 turn step is 30 x dt / 20; the +4 target is the
 * actor named by the overlay's +0x3660 hit record when its +4 owner matches ours, else the
 * closest one (cab14), and the +0x10 heading aims from the actor's +0xb0 position at the
 * target's +0x190. Once the +0x40 timer reaches 0x800 the 4-byte message at +0x3604 goes to the
 * actor's +0x24 hook with command 4, animation 5 plays, the +0x39c motion handle is reset, bit 6
 * of the +0x60 high byte is set, the timer and the +0x51 byte are cleared, reaction 0x11a/4
 * fires at the +8 anchor and the d2e54 tick takes over.
 *
 * Codegen: the record's actor is read a second time through an `int *` view of the record
 * ((int *)&record)[2]) for the owner comparison; a plain field re-read is CSE'd into one load. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

struct Ov293Owner {
    char pad000[4];
    int nOwner04;
    char pad008[0x1c];
    void (*pfnMessage)(struct Ov293Owner *self, void *msg, int size);
};

struct Ov293HitRecord {
    int nKind;
    int pad04;
    struct Ov293Owner *pActor;  /* +0x08 */
};

extern int Ov107_FindNearestObject(struct Ov293Owner *actor, int mode);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern void Ov107_BuildAndSendUpdate(struct Ov293Owner *actor, int id, int mode, void *anchor);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov293_SwingTick(int *node);
extern struct Ov293HitRecord data_ov293_020d3660;
struct Msg4 { u16 a, b; };
extern const struct Msg4 data_ov293_020d3604;

void Ov293_IdleTick(int *node)
{
    int *state = (int *)node[1];
    struct Msg4 msg;
    VecFx32 d;

    state[5] = *(int *)(*node + 0x2c) * 30 / 20;
    if (data_ov293_020d3660.pActor != 0) {
        if (((struct Ov293Owner *)((int *)&data_ov293_020d3660)[2])->nOwner04 == ((struct Ov293Owner *)state[0])->nOwner04) {
            state[1] = (int)data_ov293_020d3660.pActor;
        } else {
            state[1] = Ov107_FindNearestObject((struct Ov293Owner *)state[0], 0);
        }
        if (state[1] != 0) {
            VEC_Subtract((void *)(state[1] + 0x190), (char *)state[0] + 0xb0, &d);
            VEC_Normalize(&d, &d);
            state[4] = FX_Atan2(d.x, d.z);
        }
    }
    state[0x10] += *(int *)(*node + 0x2c);
    if (state[0x10] < 0x800) {
        return;
    }
    msg = data_ov293_020d3604;
    if (((struct Ov293Owner *)state[0])->pfnMessage != 0) {
        ((struct Ov293Owner *)state[0])->pfnMessage((struct Ov293Owner *)state[0], &msg, 4);
    }
    Ov107_PostTagUpdate((Actor *)((struct Ov293Owner *)state[0]), 5, 0);
    Ov107_StartAnim(*(int *)(state[0] + 0x39c), 0, 0);
    {
        u16 hw = *(u16 *)(state[0] + 0x60);
        *(u16 *)(state[0] + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    state[0x10] = 0;
    *(u8 *)((char *)state + 0x51) = 0;
    Ov107_BuildAndSendUpdate((struct Ov293Owner *)state[0], 0x11a, 4, (void *)state[2]);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov293_SwingTick);
}
