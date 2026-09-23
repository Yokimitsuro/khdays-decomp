/* Shockwave tick of the ov208 enemy (x3 with ov209/ov268). While the +0x2c timer (fed by the
 * owner's rate) is at most 0x3b8, an axis-aligned box centred on the +0x20 point with half-extent
 * timer x 5 / 0x3b8 (fixed point) pushes every entity whose +0x1b4 kind bit is clear in the +0x4e
 * mask away by 0x800 (kind 1); on acceptance effect 1 spawns at the entity's +0x74 position,
 * reaction 0x154 mode 9 fires there and the kind bit is set. Once the +0x50 idle byte clears
 * sub-state 2 is requested and the state ends. */
typedef unsigned char u8;

typedef struct Vec3 { int x, y, z; } Vec3;

struct BoxQuery {
    Vec3 vCenter;
    Vec3 vAxisX;
    Vec3 vAxisZ;
    Vec3 vAxisY;
    int nExtent;
    int bFlag;
};

extern int func_ov107_020c8fd0(int owner, struct BoxQuery *query, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *a, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;

void func_ov209_020d5064(int *node)
{
    int *state = (int *)node[1];
    int hits[4];
    struct BoxQuery query;
    Vec3 push;
    Vec3 at;
    int n;
    int i;

    state[0xb] += *(int *)(*node + 0x2c);
    if (state[0xb] <= 0x3b8) {
        query.vCenter = *(Vec3 *)(state + 8);
        query.vAxisX = data_02042270;
        query.vAxisZ = data_02042258;
        query.vAxisY = data_02042264;
        query.nExtent = (state[0xb] * 5 << 12) / 0x3b8;
        query.bFlag = 1;
        n = func_ov107_020c8fd0(*state, &query, hits);
        i = 0;
        if (n > 0) {
            do {
                if (((*((u8 *)state + 0x4e) >> *(u8 *)(hits[i] + 0x1b4)) & 1) == 0) {
                    VEC_Subtract((void *)(hits[i] + 0x74), &query.vCenter, &push);
                    func_01ff8d18(&push, &push);
                    func_01ffa724(0x800, &push, &push);
                    if (func_ov107_020ca918(hits[i], *state, *state, 1, &push, 0) != 0) {
                        at = *(Vec3 *)(hits[i] + 0x74);
                        func_ov107_020c0b90(*state, 1, at, 0);
                        func_ov107_020c5af8(*state, 0x154, 9, &at);
                        *((u8 *)state + 0x4e) |= 1 << *(u8 *)(hits[i] + 0x1b4);
                    }
                }
            } while (++i < n);
        }
    }
    if (*(u8 *)state[0x14] != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
