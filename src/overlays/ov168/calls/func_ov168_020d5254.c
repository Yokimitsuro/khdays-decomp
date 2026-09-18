/* Circle tick of the ov166 enemy (x3: ov166/167/168), the func_ov178_020cdbc8 shape: acquires
 * a target (+0xc; none requests sub-state 2), steps towards it along the direction from
 * 020cca08 (0x200 when the distance exceeds 0x100) plus a sideways component (world Y x
 * direction, normalised, times the +0x60 orbit sense x 0x180) into +0x20; the +0x24 height
 * tracks the target's +0x78 by 0x80 per tick outside a 0x80 dead band. The +0x5c timer runs
 * down by the node's +0x2c speed; at zero a roll under 60 (of 101) with a free target
 * (020ccaa0) requests sub-state 8, else 5, and the slot is cleared unless the sub-state stayed
 * idle. `+ (dist - dist)` is the documented copy artifact of func_02023eb4. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int b);
extern void func_0203c634(int node, int slot, void *cb);
extern int func_ov168_020d4288(int node, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_ov168_020d4320(int node);
extern int data_02042264;

void func_ov168_020d5254(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 dir;
    Vec3 side;
    int dist;
    int a;
    int b;
    int diff;
    int roll;

    state[3] = func_ov107_020cab14(*state, 0);
    if (state[3] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    dist = func_ov168_020d4288(node, &dir);
    if (dist > 0x100) {
        dist = 0x200;
    }
    func_01ffa724(dist, &dir, (Vec3 *)(state + 8));
    VEC_CrossProduct((Vec3 *)&data_02042264, &dir, &side);
    func_01ff8d18(&side, &side);
    func_01ffa724(state[0x18] * 0x180, &side, &side);
    VEC_Add((Vec3 *)(state + 8), &side, (Vec3 *)(state + 8));
    a = *(int *)(state[3] + 0x78);
    b = *(int *)(state[2] + 4);
    diff = a - b;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff > 0x80) {
        if (a < b) {
            state[9] -= 0x80;
        } else {
            state[9] += 0x80;
        }
    }
    state[0x17] -= *(int *)(*(int *)node + 0x2c);
    if (state[0x17] > 0) {
        return;
    }
    roll = func_02023eb4(0x65) + (dist - dist);
    state[0x17] = 0;
    *(unsigned char *)(*state + 0x1c7) = (roll < 0x3c && func_ov168_020d4320(node) != 0) ? 8 : 5;
    if (*(signed char *)(*state + 0x1c7) != -1) {
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
    }
}
