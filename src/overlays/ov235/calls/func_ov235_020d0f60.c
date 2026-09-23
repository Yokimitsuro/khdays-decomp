/* Aim tick of an ov235 state: the +0x40 rate is the frame rate x 6; the nearest target (020cab14)
 * becomes +0x5c and, when there is one, the +0x2c orientation looks at it (0203cd7c about
 * data_02042264) and +0x68 takes the unit direction from the owner to the target's centre
 * (+0x74 raised by its +0x80 height); without one +0x68 is zeroed. Once the +0xc idle byte clears,
 * the owner's +0x24 hook receives note 1 of data_ov235_020d24d0, animation 0x20 plays, +0x63,
 * +0x44 and the owner's +0x64 velocity clear, reaction +0x3c8 fires with modes 0x22 and 0x10 at
 * the +4 point and the tick hands over to func_ov235_020d10ec. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { int m[9]; } Mtx33;
typedef struct { u16 lo; u16 hi; } Cmd4;
typedef struct { Vec3 pos; int height; } Body;

extern const struct { Cmd4 n[4]; } data_ov235_020d24d0;
extern int func_ov107_020cab14(int obj, int kind);
extern void func_0203cd7c(Mtx33 *out, const Vec3 *at, const Vec3 *from, const Vec3 *up);
extern void func_0202ea48(Quat *out, const Mtx33 *m);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d10ec(int *node);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

static inline void VEC_Set(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov235_020d0f60(int *node)
{
    int owner;
    int *state = (int *)node[1];
    Body *body;
    Mtx33 m;
    Vec3 centre;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 5;
    body = (Body *)(state[0x17] = func_ov107_020cab14(*state, 0));
    if (body != 0) {
        owner = *state;

        body = (Body *)((char *)body + 0x74);
        centre = body->pos;
        centre.y += body->height;
        func_0203cd7c(&m, &body->pos, (Vec3 *)(owner + 0x74), &data_02042264);
        func_0202ea48((Quat *)(state + 0xb), &m);
        VEC_Subtract(&centre, (void *)(owner + 0x74), (Vec3 *)(state + 0x1a));
        func_01ff8d18((Vec3 *)(state + 0x1a), (Vec3 *)(state + 0x1a));
    } else {
        *(Vec3 *)(state + 0x1a) = data_02041dc8;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    {
        Cmd4 note;
        Cmd4 *p = &note;

        p->hi = data_ov235_020d24d0.n[1].hi;
        p->lo = data_ov235_020d24d0.n[1].lo;

        if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
        }
    }
    func_ov107_020c9264(*state, 0x20, 0);
    *((u8 *)state + 0x63) = 0;
    state[0x11] = 0;
    VEC_Set((Vec3 *)(*state + 0x64), 0, 0, 0);
    func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x22, (void *)state[1]);
    func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x10, (void *)state[1]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d10ec);
}
