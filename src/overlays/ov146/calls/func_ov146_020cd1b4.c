/* Approach tick of the ov146 actor. With a partner guard (+0x58) it looks for the nearest target
 * (020cab14, into the actor's +0x3b4); one closer than 6.0 is circled: the +0x30 heading points at it,
 * the +0x38 radius is its distance plus 8.0, +0x34 clears, a random direction (+0x4c = +/-1) is chosen
 * and the node moves on to 020cd3b4. Otherwise it walks toward its partner (+8) at up to 0.0234 along
 * the ground-plane heading (+0x2c); within reach (both radii plus 0.0234) the next move is 5, and once
 * the +0x44 timer is out it is 6. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_02023eb4(int bound);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov146_020cd3b4(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov146_020cd1b4(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    Vec3 unit;
    Vec3 to;
    Vec3 dir;
    int dist;
    int reach;
    int flat;

    if (state[0x16] != 0) {
        *(int *)(*state + 0x3b4) = func_ov107_020cab14(*state, 0);
        if (*(int *)(*state + 0x3b4) == 0) {
            return;
        }
        VEC_Subtract((Vec3 *)(*(int *)(*state + 0x3b4) + 0x190), (Vec3 *)(*state + 0xb0), &d);
        {
            int range = func_01ff8d18(&d, &d);

            if (range >= 0x6000) {
                return;
            }
            state[0xc] = func_020050b4(d.x, d.z);
            state[0xe] = range + 0x8000;
        }
        state[0xd] = 0;
        state[0x13] = func_02023eb4(2) != 0 ? 1 : -1;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov146_020cd3b4);
        return;
    }
    reach = *(int *)(state[2] + 0x80) + 0x60 + *(int *)(*state + 0x80);
    VEC_Subtract((Vec3 *)(state[2] + 0xb0), (Vec3 *)(*state + 0xb0), &to);
    dist = func_01ff8d18(&to, &unit);
    to.y = 0;
    flat = func_01ff8d18(&to, &to);
    state[0xb] = func_020050b4(to.x, to.z);
    {
        int idx = ANG2IDX(state[0xb]) * 2;

        dir.x = data_0203d210[idx];
        dir.y = 0;
        dir.z = data_0203d210[idx + 1];
    }
    if (flat >= 0x60) {
        flat = 0x60;
    }
    func_01ffa724(flat, &dir, (Vec3 *)(state + 4));
    if (dist < reach) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x11] > 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 6;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
