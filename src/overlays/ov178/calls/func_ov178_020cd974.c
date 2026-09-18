/* Stalk tick of the ov178 enemy (x3: ov178/179/180): acquires the target (020cab14) -- none
 * sends it to sub-state 2 -- then faces it (flattened direction from the actor's +0x74 to the
 * target position at +8, atan2 into the +0x74 quaternion around the up axis) and steps 0x400
 * along it; the hover height (+0x24) eases 1/30 of the way to the target's +0x78 + 0x2a00 (or the
 * +0x18 override when +0x88 is set) above the target position. Beyond 0x3000 of surface
 * distance a 1-in-3 roll decides: 35 % with a free target (020ccb8c) go to sub-state 9, the rest
 * to 2; otherwise the +0x48 phase advances and at 0x3000 sub-state 6 follows. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int b);
extern void func_0203c634(int node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int y, int x);
extern void func_0202f188(void *quat, void *axis, int angle);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_ov178_020ccb8c(int node);
extern int data_02042264;

void func_ov178_020cd974(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 d;
    int dist;
    int target;
    int obj;
    int height;
    int diff;

    state[3] = func_ov107_020cab14(*state, 0);
    if (state[3] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)state[2], (Vec3 *)(state[3] + 0x74), &d);
    d.y = 0;
    target = state[3];
    obj = *state;
    dist = func_01ff8d18(&d, &d) - *(int *)(target + 0x80) - *(int *)(obj + 0x80);
    func_0202f188(state + 0x1d, &data_02042264, func_020050b4(d.x, d.z));
    func_01ffa724(0x400, &d, (Vec3 *)(state + 8));
    if (state[0x22] != 0) {
        height = state[6];
    } else {
        height = *(int *)(state[3] + 0x78) + 0x2a00;
    }
    diff = height - *(int *)(state[2] + 4);
    state[9] += (int)(((long long)(diff / 30) * 0x2000 + 0x800) >> 12);
    if (dist > 0x3000 && func_02023eb4(3) == 0) {
        if ((unsigned int)func_02023eb4(100) < 0x23 && func_ov178_020ccb8c(node) != 0) {
            *(unsigned char *)(*state + 0x1c7) = 9;
            func_0203c634(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    state[0x12] += *(int *)(*(int *)node + 0x2c);
    if (state[0x12] >= 0x3000) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
    }
}
