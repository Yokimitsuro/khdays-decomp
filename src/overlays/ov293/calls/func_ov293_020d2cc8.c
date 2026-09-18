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
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Vec3 { int x, y, z; } Vec3;

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

extern int func_ov107_020cab14(struct Ov293Owner *actor, int mode);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(struct Ov293Owner *actor, int anim, int flag);
extern void func_ov107_020c9ee8(int handle, int a, int b);
extern void func_ov107_020c5af8(struct Ov293Owner *actor, int id, int mode, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov293_020d2e54(int *node);
extern struct Ov293HitRecord data_ov293_020d3660;
struct Msg4 { u16 a, b; };
extern const struct Msg4 data_ov293_020d3604;

void func_ov293_020d2cc8(int *node)
{
    int *state = (int *)node[1];
    struct Msg4 msg;
    Vec3 d;

    state[5] = *(int *)(*node + 0x2c) * 30 / 20;
    if (data_ov293_020d3660.pActor != 0) {
        if (((struct Ov293Owner *)((int *)&data_ov293_020d3660)[2])->nOwner04 == ((struct Ov293Owner *)state[0])->nOwner04) {
            state[1] = (int)data_ov293_020d3660.pActor;
        } else {
            state[1] = func_ov107_020cab14((struct Ov293Owner *)state[0], 0);
        }
        if (state[1] != 0) {
            VEC_Subtract((void *)(state[1] + 0x190), (char *)state[0] + 0xb0, &d);
            func_01ff8d18(&d, &d);
            state[4] = func_020050b4(d.x, d.z);
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
    func_ov107_020c9264((struct Ov293Owner *)state[0], 5, 0);
    func_ov107_020c9ee8(*(int *)(state[0] + 0x39c), 0, 0);
    {
        u16 hw = *(u16 *)(state[0] + 0x60);
        *(u16 *)(state[0] + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    state[0x10] = 0;
    *(u8 *)((char *)state + 0x51) = 0;
    func_ov107_020c5af8((struct Ov293Owner *)state[0], 0x11a, 4, (void *)state[2]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov293_020d2e54);
}
