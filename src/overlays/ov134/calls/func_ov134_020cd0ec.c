/* Chase tick of the ov134 enemy (x3: ov134/135/136), ported from the matched ov194 sibling:
 * acquires a target (+8) -- none requests sub-state 2 and drops the slot; steers the +0x18
 * velocity along the facing (+0xc) from the sin/cos table, scaled by the +0x3a0 resource's rate
 * and doubled while the +0x42 bit-0 flag (charging) is set; charging ends the state once the
 * target is within 0x1000, otherwise the state ends when the distance leaves the
 * [0x6000, +0x2d8] band, clearing the +0xa8 byte of the +4 sub-item and advancing to
 * func_ov134_020cd2a8. */
struct Flags42 { unsigned char bCharge : 1; };
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int mode);
extern void func_0203c634(int node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_ov107_020c9f48(int resource, int a);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov134_020cd2a8(void);
extern const short data_0203d210[];

void func_ov134_020cd0ec(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 d;
    Vec3 fwd;
    int idx;
    int dist;
    int boost;
    int speed;
    int actor;
    int target;

    state[2] = func_ov107_020cab14(*state, 0);
    if (state[2] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0xb0), &d);
    d.y = 0;
    actor = *state;
    target = state[2];
    dist = func_01ff8d18(&d, &d) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    state[4] = func_020050b4(d.x, d.z);
    idx = (unsigned short)((0x28BE60DB9391LL * state[3] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    fwd.x = data_0203d210[(idx >> 4) << 1];                                              /* FX_SinIdx */
    fwd.z = data_0203d210[((idx >> 4) << 1) + 1];                                        /* FX_CosIdx */
    fwd.y = 0;
    boost = ((struct Flags42 *)((char *)state + 0x42))->bCharge ? 2 : 1;
    speed = func_ov107_020c9f48(*(int *)(*state + 0x3a0), 0);
    func_01ffa724(boost * speed, &fwd, (Vec3 *)(state + 6));
    if (((struct Flags42 *)((char *)state + 0x42))->bCharge) {
        if (dist > 0x1000) {
            return;
        }
        *(unsigned char *)(state[1] + 0xa8) = 0;
        func_0203c634(node, *(signed char *)(node + 0x20), func_ov134_020cd2a8);
        return;
    }
    if (dist >= 0x6000 && dist <= *(int *)(*state + 0x2d8)) {
        return;
    }
    *(unsigned char *)(state[1] + 0xa8) = 0;
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov134_020cd2a8);
}
