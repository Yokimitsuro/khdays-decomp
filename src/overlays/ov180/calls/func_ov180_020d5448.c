/* Circle tick of the ov178 enemy (x3: ov178/179/180): acquires the target -- none sends it to
 * sub-state 2 -- then steps towards it (the target direction from 020ccaf4 scaled by its
 * distance, capped at 0x200) plus a tangential component (up x direction, normalised, scaled by
 * the +0x60 orbit sense times 0x180); the hover height (+0x24) tracks the target's +0x78 by 0x80
 * per tick outside a 0x80 dead band. The +0x5c timer runs down by the node's +0x2c speed and,
 * while no target is free (020ccb8c), keeps being re-armed to a random value between the actor's
 * +0x224 and +0x228; at zero a roll picks sub-state 9 (40 %) or 8 (60 %) when a target is free,
 * else 5, and the slot is cleared unless the sub-state stayed idle.
 * `+ (dist - dist)` is the documented copy artifact of func_02023eb4 (`add r6,r0,#0`). */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int b);
extern void func_0203c634(int node, int slot, void *cb);
extern int func_ov180_020d4374(int node, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov180_020d440c(int node);
extern int func_02023eb4(int bound);
extern int data_02042264;

void func_ov180_020d5448(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 dir;
    Vec3 side;
    int dist;
    int a;
    int b;
    int diff;
    int lo;
    int roll;

    state[3] = func_ov107_020cab14(*state, 0);
    if (state[3] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    dist = func_ov180_020d4374(node, &dir);
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
    if (func_ov180_020d440c(node) == 0) {
        lo = *(int *)(*state + 0x224);
        diff = *(int *)(*state + 0x228) - lo;
        if (diff < 0) {
            diff = -diff;
        }
        state[0x17] = lo + func_02023eb4(diff + 1);
    }
    if (state[0x17] > 0) {
        return;
    }
    roll = func_02023eb4(0x65) + (dist - dist);
    state[0x17] = 0;
    if (roll < 0x28 && func_ov180_020d440c(node) != 0) {
        *(unsigned char *)(*state + 0x1c7) = 9;
    } else if (roll < 0x3c && func_ov180_020d440c(node) != 0) {
        *(unsigned char *)(*state + 0x1c7) = 8;
    } else {
        *(unsigned char *)(*state + 0x1c7) = 5;
    }
    if (*(signed char *)(*state + 0x1c7) != -1) {
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
    }
}
