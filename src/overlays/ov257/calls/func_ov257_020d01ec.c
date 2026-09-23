/* Glide-in tick of an ov257 state: the +0x50 timer accumulates the owner's rate and the +0x5c path
 * point is resolved (func_ov257_020ccf98) into the +0x10 step. Once the +0xc idle byte clears, the
 * owner's +0x24 hook receives note 2 of data_ov257_020d325c, animation 0x16 plays looped, +0x44,
 * +0x48 and +0x65 clear, +0x68 takes the owner's hit points (+0x21a) as a fixed-point value and the
 * tick hands over to func_ov257_020d02c8. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 lo; u16 hi; } Cmd4;

extern void func_ov257_020ccf98(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd4 data_ov257_020d325c[];
extern void func_ov257_020d02c8(int *node);

void func_ov257_020d01ec(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x15] += *(int *)(node[0] + 0x2c);
    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    {
        Cmd4 note;
        Cmd4 *p = &note;

        p->hi = data_ov257_020d325c[2].hi;
        p->lo = data_ov257_020d325c[2].lo;
        if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
        }
    }
    func_ov107_020c9264(*state, 0x16, 1);
    state[0x11] = 0;
    state[0x12] = 0;
    *((unsigned char *)state + 0x76) = 0;
    state[0x17] = *(short *)(*state + 0x200 + 0x1a) << 12;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d02c8);
}
