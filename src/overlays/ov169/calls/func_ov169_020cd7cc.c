/* Hover-approach tick of the ov169 enemy (and its byte-identical twins): acquires a target (+0xc; none
 * requests sub-state 2); the flattened, normalised offset from the target's +0x74 to the +8
 * position gives the surface distance (length minus both +0x80 radii) and the heading, which
 * becomes the +0x74 orientation (quaternion about world Y) and, at 0.25, the +0x20 step. The
 * +0x24 height eases towards the target's +0x78 plus 3.0 (or the fixed +0x18 height when
 * +0x88 is set) by half the difference per second. Beyond 3.0 a 1/3 roll picks sub-state 8
 * with a free target (020ccaa0) or 2; otherwise the +0x48 timer grows and past 3.0 requests
 * sub-state 6. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int mode);
extern void func_0203c634(int node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_0202f188(int *out, const int *axis, int angle);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_ov169_020ccacc(int node);
extern int data_02042264;

void func_ov169_020cd7cc(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 dir;
    int dist;
    int target;
    int obj;
    int h;
    int diff;

    state[3] = func_ov107_020cab14(*state, 0);
    if (state[3] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)state[2], (Vec3 *)(state[3] + 0x74), &dir);
    dir.y = 0;
    obj = *state;
    target = state[3];
    dist = func_01ff8d18(&dir, &dir) - *(int *)(target + 0x80) - *(int *)(obj + 0x80);
    func_0202f188(state + 0x1d, &data_02042264, func_020050b4(dir.x, dir.z));
    func_01ffa724(0x300, &dir, (Vec3 *)(state + 8));
    h = state[0x22] != 0 ? state[6] : *(int *)(state[3] + 0x78) + 0x3c00;
    diff = h - *(int *)(state[2] + 4);
    state[9] += (int)(((long long)(diff / 30) * 0x1800 + 0x800) >> 12);
    if (dist > 0x3000 && func_02023eb4(3) == 0) {
        if (func_ov169_020ccacc(node) != 0) {
            *(unsigned char *)(*state + 0x1c7) = 8;
            func_0203c634(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    state[0x12] += *(int *)(*(int *)node + 0x2c);
    if (state[0x12] < 0x3000) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 6;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
