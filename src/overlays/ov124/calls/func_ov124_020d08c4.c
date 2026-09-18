/* Approach decision of the ov123 enemy (and its byte-identical twin): the target picked by
 * cd224 goes to +0x24 (none returns); the +0x20 step is 30 x dt / 20 and the surface distance
 * (root minus both +0x80 radii) must be inside the actor's +0x2d8 range. The +0x1c heading aims
 * at the target's +0x190 from the +0x10 position. Within 0x1000 with the target ahead (forward
 * . direction >= 0.875) the +0x28 timer is re-armed at random between the actor's +0x224 and
 * +0x228 and sub-state 4 is requested; otherwise the timer counts down and, once spent, does the
 * same -- both only while the +0x394 item's +0x60 low bit is clear. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern int func_ov124_020d0e64(int actor, int *distOut);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern int func_02023eb4(int bound);
extern void func_0203c634(int node, int slot, void *cb);
extern const Vec3 data_02042258;

void func_ov124_020d08c4(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 d;
    Vec3 fwd;
    int dist;
    int target;
    int obj;
    int lo;
    int diff;

    state[9] = func_ov124_020d0e64(*state, &dist);
    if (state[9] == 0) {
        return;
    }
    state[8] = *(int *)(*(int *)node + 0x2c) * 30 / 20;
    target = state[9];
    obj = *state;
    dist = FX_Sqrt(dist) - *(int *)(target + 0x80) - *(int *)(obj + 0x80);
    if (dist >= *(int *)(*state + 0x2d8)) {
        return;
    }
    VEC_Subtract((Vec3 *)(state[9] + 0x190), (Vec3 *)state[4], &d);
    func_01ff8d18(&d, &d);
    func_0202f384(&fwd, (void *)(*state + 0xa0), &data_02042258);
    if (dist < 0x1000 && VEC_DotProduct(&fwd, &d) >= 0xe00) {
        state[7] = func_020050b4(d.x, d.z);
        if ((((struct hw60 *)(*(int *)(*state + 0x394) + 0x60))->lo & 1) != 0) {
            return;
        }
        lo = *(int *)(*state + 0x224);
        diff = *(int *)(*state + 0x228) - lo;
        if (diff < 0) {
            diff = -diff;
        }
        state[10] = lo + func_02023eb4(diff + 1);
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    state[7] = func_020050b4(d.x, d.z);
    if ((((struct hw60 *)(*(int *)(*state + 0x394) + 0x60))->lo & 1) != 0) {
        return;
    }
    state[10] -= *(int *)(*(int *)node + 0x2c);
    if (state[10] > 0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    diff = *(int *)(*state + 0x228) - lo;
    if (diff < 0) {
        diff = -diff;
    }
    state[10] = lo + func_02023eb4(diff + 1);
    *(unsigned char *)(*state + 0x1c7) = 4;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
