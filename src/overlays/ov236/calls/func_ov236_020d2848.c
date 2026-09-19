/* Charge-in tick: refreshes the +4 target (none: pose request 9), measures the surface gap
 * (root of the squared distance minus both +0x80 radii), counts the +0x3c timer down, heads for
 * the target (+0x30 = atan2 of the flattened, normalised offset, +8 velocity = the gap capped
 * at 0.5 along it, then dropped by 0x400 in y). Once the +0x24 child's byte clears the cue at
 * data_ov236_020d63e8 entry 6 goes through the +0x24 hook, the actor's +0x54 becomes 3.0, the
 * +0x14 word clears and the node moves to 020d29b8. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern void func_0203c634(int *node, int slot, void *cb);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern unsigned short data_ov236_020d63e8[];
extern void func_ov236_020d29b8(void);

void func_ov236_020d2848(int *node) {
    int *state = (int *)node[1];
    Vec3 d;
    int dist;
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();
    int actor;
    int target;

    target = state[1] = func_ov107_020cab14(*state, &dist);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 9;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    actor = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    state[0xf] -= *(int *)(*node + 0x2c);
    VEC_Subtract((Vec3 *)(state[1] + 0x74), (Vec3 *)(*state + 0x74), &d);
    d.y = 0;
    {
        int actor = state[0];
        int target = state[1];
        dist = func_01ff8d18(&d, &d) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    }
    state[0xc] = func_020050b4(d.x, d.z);
    func_01ffa724(dist >= 0x800 ? 0x800 : dist, &d, (Vec3 *)(state + 2));
    state[3] -= 0x400;
    if (*(unsigned char *)state[9] != 0) {
        return;
    }
    pp = pair;
    pp[1] = data_ov236_020d63e8[13];
    pp[0] = data_ov236_020d63e8[12];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    *(int *)(*state + 0x54) = 0x3000;
    state[5] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov236_020d29b8);
}
