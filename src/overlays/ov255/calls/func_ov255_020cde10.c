/* Dive tick of an ov255 state: the +0x40 rate clears, the +0x5c path point is resolved
 * (func_ov255_020ccdac) into the +0x10 step and the +0x50 timer accumulates the owner's rate; past
 * 0x911, once (+0x65), reaction +0x3f8 (as a halfword) mode 3 fires at the +4 point. Once the +0xc
 * idle byte clears and the owner is grounded (+0x17a bit 0), animation 6 plays, the +0x3a4 part
 * plays motion 5 and the tick hands over to func_ov255_020cdf08. */
typedef struct { int x, y, z; } Vec3;
struct Bits17a { unsigned char b0 : 1; };

extern void func_ov255_020ccdac(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov255_020cdf08(int *node);

void func_ov255_020cde10(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x10] = 0;
    func_ov255_020ccdac(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    state[0x14] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x65) == 0 && state[0x14] >= 0x911) {
        func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3f8), 3, (void *)state[1]);
        *((unsigned char *)state + 0x65) = 1;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    if (((struct Bits17a *)(*state + 0x17a))->b0 == 0) {
        return;
    }
    func_ov107_020c9264(*state, 6, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a4), 5, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020cdf08);
}
