/* Hover-bob tick of the ov178 enemy (x3: ov178/179/180): acquires the target -- none sends it
 * to sub-state 2 -- steps 0x300 along the target direction and bobs: the +0x50 phase advances
 * by 30x the node's +0x2c speed and wraps at +0x54 seconds (re-rolled to 40 + rand(1)); the
 * hover height eases 1/10 of the way to the target's +0x78 + 0x1c00 (lowered by however much
 * the +0x44 target height exceeds 0x1c00; the +0x18 override when +0x88 is set) plus half a
 * sine of the phase over the period, scaled by 0x800. With no free target (020ccb8c) the
 * x/z step is halved instead; otherwise closer than 0x2000 the actor drops to sub-state 2.
 * The bob index is the SDK macro verbatim (`FX_RAD_TO_IDX`: constant on the left, `+ 0x80000000000LL`,
 * `>> 44` into a u16) and `FX_SinIdx` as `table[(idx >> 4) << 1]`; the ov117 `>> 32` spelling
 * swaps the chain's registers here. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int b);
extern void func_0203c634(int node, int slot, void *cb);
extern int func_ov178_020ccaf4(int node, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_02020400(int a, int b);
extern int func_ov178_020ccb8c(int node);
extern short data_0203d210[];

void func_ov178_020cd6e0(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 dir;
    int dist;
    int h;
    int t;
    int idx;
    int s;
    int diff;

    state[3] = func_ov107_020cab14(*state, 0);
    if (state[3] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    dist = func_ov178_020ccaf4(node, &dir);
    func_01ffa724(0x300, &dir, (Vec3 *)(state + 8));
    state[9] = 0;
    state[0x14] += *(int *)(*(int *)node + 0x2c) * 30;
    if (state[0x14] >= state[0x15] << 12) {
        state[0x14] = 0;
        state[0x15] = func_02023eb4(1) + 0x28;
    }
    if (state[0x22] == 0) {
        h = *(int *)(state[3] + 0x78) + 0x1c00;
        if (state[0x11] > 0x1c00) {
            h -= state[0x11] - 0x1c00;
        }
    } else {
        h = state[6];
    }
    t = func_02020400((int)(((long long)state[0x14] * 0x6488 + 0x800) >> 12), state[0x15]);
    idx = (unsigned short)((0x28BE60DB9391LL * t + 0x80000000000LL) >> 44);          /* FX_RAD_TO_IDX */
    s = data_0203d210[(idx >> 4) << 1] / 2;                                            /* FX_SinIdx / 2 */
    diff = h + (int)(((long long)s * 0x800 + 0x800) >> 12) - *(int *)(state[2] + 4);
    state[9] += (int)(((long long)(diff / 10) * 0x2000 + 0x800) >> 12);
    if (func_ov178_020ccb8c(node) == 0) {
        state[8] = (int)(((long long)state[8] * 0x800 + 0x800) >> 12);
        state[10] = (int)(((long long)state[10] * 0x800 + 0x800) >> 12);
        return;
    }
    if (dist >= 0x2000) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
