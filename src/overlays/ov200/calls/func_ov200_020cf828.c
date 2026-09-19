/* Circle tick of the ov200 enemy (x3: ov200/ov201/ov271): acquires the target into +8 -- none
 * sends it to sub-state 2 -- then steps towards it (the normalised owner-to-target direction
 * scaled by the gap beyond both radii plus 0x800, capped at 0x400) plus a tangential component
 * (up x direction, normalised, scaled by the +0xa4 orbit sense times 0x400) into +0xc; the
 * look-at at +0x94 is rebuilt from the two +0x74 positions and the hover height (+0x10) tracks
 * the target's +0x78 by 0x40 per tick outside a 0x80 dead band. The +0x50 timer accumulates
 * the rate; while the +0x80 count is spent a 0x65 roll (discarded) re-arms it to a random
 * value between the actor's +0x224 and +0x228, and sub-state 6 is queued when the three
 * +0x390/+0x394/+0x398 aim nodes are all idle (ov200 055c), 7 when only the last two are.
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
extern int func_ov200_020d055c(int node);
extern int data_02042264;

void func_ov200_020cf828(int *node)
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

    target = state[2] = func_ov107_020cab14(*state, 0);
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
    func_0202ea48(state + 0x25, buf);
    if (dist > 0x400) {
        dist = 0x400;
    }
    func_01ffa724(dist, &dir, (Vec3 *)(state + 3));
    VEC_CrossProduct((Vec3 *)&data_02042264, &dir, &side);
    func_01ff8d18(&side, &side);
    func_01ffa724(state[0x29] << 10, &side, &side);
    VEC_Add((Vec3 *)(state + 3), &side, (Vec3 *)(state + 3));
    b = *(int *)(actor + 0x78);
    a = *(int *)(target + 0x78);
    diff = a - b;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff > 0x80) {
        if (a < b) {
            state[4] -= 0x40;
        } else {
            state[4] += 0x40;
        }
    }
    state[0x14] += *(int *)(node[0] + 0x2c);
    if (state[0x20] <= 0) {
        roll = func_02023eb4(0x65) + (dist - dist);
        lo = *(int *)(*state + 0x224);
        diff = *(int *)(*state + 0x228) - lo;
        if (diff < 0) {
            diff = -diff;
        }
        state[0x20] = lo + func_02023eb4(diff + 1);
        if (func_ov200_020d055c(*(int *)(*state + 0x390)) != 0
            && func_ov200_020d055c(*(int *)(*state + 0x394)) != 0
            && func_ov200_020d055c(*(int *)(*state + 0x398)) != 0) {
            *(unsigned char *)(*state + 0x1c7) = 6;
            func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
            return;
        }
        if (func_ov200_020d055c(*(int *)(*state + 0x394)) == 0) {
            return;
        }
        if (func_ov200_020d055c(*(int *)(*state + 0x398)) == 0) {
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 7;
        func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
    }
}
