/* Hover-in tick of an ov255 state: the +0x50 timer accumulates the owner's rate and the +0x5c path
 * point is resolved (func_ov255_020ccdac) into the +0x10 step. Once the +0xc idle byte clears, the
 * owner's +0x24 hook receives note 7 of data_ov255_020d2b20, animation 0x19 plays, +0x44 and +0x65
 * clear and the tick hands over to func_ov255_020d09cc. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 lo; u16 hi; } Cmd4;

extern void func_ov255_020ccdac(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd4 data_ov255_020d2b20[];
extern void func_ov255_020d09cc(int *node);

void func_ov255_020d0908(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x14] += *(int *)(node[0] + 0x2c);
    func_ov255_020ccdac(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    {
        Cmd4 note;
        Cmd4 *p = &note;

        p->hi = data_ov255_020d2b20[7].hi;
        p->lo = data_ov255_020d2b20[7].lo;
        if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
        }
    }
    func_ov107_020c9264(*state, 0x19, 0);
    state[0x11] = 0;
    *((unsigned char *)state + 0x65) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020d09cc);
}
