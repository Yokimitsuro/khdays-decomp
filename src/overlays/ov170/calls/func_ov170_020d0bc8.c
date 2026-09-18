/* Sweep step of the ov169 enemy (x2: ov169/170): while the +0x44 timer stays within 0xbb0 it
 * runs the attack sweep (func_ov170_020d0244) with a query built from the +8 position raised by
 * 0xc00, the up axis, a 0x3000 range and a 0xc00 radius; afterwards sub-state 0 is requested. */
typedef struct { int x, y, z; } Vec3;

struct Ov169SweepQuery {
    Vec3 vPos;
    Vec3 vAxis;
    int nRange;
    int nRadius;
};

extern const Vec3 data_02042264;
extern void func_ov170_020d0244(int *state, int kind, struct Ov169SweepQuery *query);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov170_020d0bc8(int *node)
{
    int *state = (int *)node[1];
    struct Ov169SweepQuery query;

    state[0x11] += *(int *)(*node + 0x2c);
    if (state[0x11] <= 0xbb0) {
        query.vAxis = data_02042264;
        query.nRadius = 0xc00;
        query.nRange = 0x3000;
        query.vPos = *(Vec3 *)state[2];
        query.vPos.y += query.nRadius;
        func_ov170_020d0244(state, 0, &query);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
