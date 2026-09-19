/* Decision tick of the ov274 enemy. The target is re-acquired into +0x10 (none: sub-state 2
 * and the state ends). The flattened direction from the +4 point to the target's +0x190 gives
 * the gap (less both +0x80 radii), the +0x3c rate takes 30 x rate / 30 and +0x44 the heading
 * (atan2 of the direction). The +0x14 aim takes the owner's +0xa0 basis turned by the +0x3b4
 * aim (9f48), scaled by its reach and normalised. Once the +0xc idle byte is clear a roll of
 * 101 decides: under 20 sub-state 0xa, under 40 sub-state 5; otherwise, closer than 4.0 a dot
 * product of the direction and the aim above 0x200 gives sub-state 6, else nothing, and
 * farther the same test gives sub-state 5 or a second roll (under 50: 0xa, else 9). Every
 * decision ends the state. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int owner, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_ov107_020c9f48(int aim, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *basis, const Vec3 *v);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern long long func_02023eb4(int bound);
static inline int RandRange(int lo, int hi) { return (int)func_02023eb4(hi - lo + 1) + lo; }
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);

void func_ov275_020d38b8(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 aim;
    int gap;
    int target;
    int owner;
    int reach;
    int roll;

    state[4] = func_ov107_020cab14(*state, 0);
    if (state[4] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)(state[4] + 0x190), (Vec3 *)state[1], &dir);
    target = state[4];
    owner = *state;
    gap = func_01ff8d18(&dir, &dir) - (*(int *)(owner + 0x80) + *(int *)(target + 0x80));
    state[0xf] = *(int *)(node[0] + 0x2c) * 30 / 30;
    state[0x11] = func_020050b4(dir.x, dir.z);
    reach = func_ov107_020c9f48(*(int *)(*state + 0x3b4), &aim);
    func_0202f384((Vec3 *)(state + 5), (char *)*state + 0xa0, &aim);
    func_01ffa724(reach, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
    func_01ff8d18((Vec3 *)(state + 5), &aim);
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    roll = RandRange(0, 100);
    if (roll < 20) {
        *(unsigned char *)(*state + 0x1c7) = 0xa;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (roll < 40) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (gap < 0x4000) {
        if (VEC_DotProduct(&dir, &aim) <= 0x200) {
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 6;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (VEC_DotProduct(&dir, &aim) > 0x200) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    roll = RandRange(0, 100);
    if (roll < 50) {
        *(unsigned char *)(*state + 0x1c7) = 0xa;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 9;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
