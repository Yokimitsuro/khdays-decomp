/* Circle tick of the ov125 enemy: reseeds the +0x3c counter with 3 times the owner's rate
 * (30/10) and acquires the target -- none sends it to sub-state 2 -- then steps towards it (the
 * normalised owner-to-target direction scaled by the gap beyond both radii plus 0x800, capped
 * at 0x400) plus a tangential component (up x direction, normalised, scaled by the +0x78 orbit
 * sense times 0x400); the look-at at +0x68 is rebuilt from the two +0x74 positions and the
 * hover height (+0xc) tracks the target's +0x78 by 0x40 per tick outside a 0x80 dead band. The
 * +0x2c timer accumulates the rate; while the +0x54 count is spent a 0x65 roll re-arms it to a
 * random value between the actor's +0x224 and +0x228 and picks sub-state 6 (under 20 with an
 * idle aim node) or 7; otherwise past 0x2000 sub-state 4 is queued.
 * `+ (dist - dist)` is the documented copy artifact of func_02023eb4 (`add r5,r0,#0`). */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int b);
extern void func_0203c634(int node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0203cd7c(void *out, void *a, void *b, void *c);
extern void func_0202ea48(void *a, void *b);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_ov125_020ce594(int node);
extern int data_02042264;

void func_ov125_020cd840(int *node)
{
    int actor;
    int target;
    int *state = (int *)node[1];
    int dist;
    int len;
    int sum;
    int buf[9];
    Vec3 dir;
    Vec3 side;
    int b;
    int a;
    int diff;
    int lo;
    int roll;

    state[0xf] = *(int *)(node[0] + 0x2c) * 30 / 10;
    target = state[1] = func_ov107_020cab14(*state, 0);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    actor = *state;
    VEC_Subtract((Vec3 *)(target + 0x74), (Vec3 *)(actor + 0x74), &dir);
    len = func_01ff8d18(&dir, &dir);
    sum = *(int *)(target + 0x80) + *(int *)(actor + 0x80) + 0x800;
    dist = len > sum ? len - sum : 0;
    func_0203cd7c(buf, (void *)(target + 0x74), (void *)(actor + 0x74), &data_02042264);
    func_0202ea48(state + 0x1a, buf);
    if (dist > 0x400) {
        dist = 0x400;
    }
    func_01ffa724(dist, &dir, (Vec3 *)(state + 2));
    VEC_CrossProduct((Vec3 *)&data_02042264, &dir, &side);
    func_01ff8d18(&side, &side);
    func_01ffa724(state[0x1e] << 10, &side, &side);
    VEC_Add((Vec3 *)(state + 2), &side, (Vec3 *)(state + 2));
    b = *(int *)(actor + 0x78);
    a = *(int *)(target + 0x78);
    diff = a - b;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff > 0x80) {
        if (a < b) {
            state[3] -= 0x40;
        } else {
            state[3] += 0x40;
        }
    }
    state[0xb] += *(int *)(node[0] + 0x2c);
    if (state[0x15] <= 0) {
        roll = func_02023eb4(0x65) + (dist - dist);
        lo = *(int *)(*state + 0x224);
        diff = *(int *)(*state + 0x228) - lo;
        if (diff < 0) {
            diff = -diff;
        }
        state[0x15] = lo + func_02023eb4(diff + 1);
        if (roll < 0x14 && func_ov125_020ce594(*(int *)(*state + 0x390)) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 6;
            func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 7;
        func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    if (state[0xb] <= 0x2000) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
}
