/* Walk tick of the ov227 enemy: when the tracking step (func_ov227_020d14bc) reports the target
 * lost the tick ends; otherwise the +0x58 heading faces the +0x38 goal from the +8 point. While the
 * rig is busy (+0xad) the enemy keeps steering along it (func_ov227_020d2568); once it is free, a
 * d100 below 30 requests move 0x10, the move chooser (func_ov227_020d0e98) may queue another, and
 * otherwise sub-state 2 is requested. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov227_020d14bc(int *node, Vec3 *dir);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int y, int x);
extern unsigned int func_02023eb4(int n);
extern int func_ov227_020d0e98(int *node, int dist);
extern void func_ov227_020d2568(int *node, int rad);

void func_ov227_020d2828(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    int dist;

    dist = func_ov227_020d14bc(node, 0);
    if (dist < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state + 0xe), (void *)state[2], &d);
    state[0x16] = func_020050b4(d.x, d.z);
    if (*(unsigned char *)(*(int *)(*state + 0x384) + 0xad) == 0) {
        if (func_02023eb4(100) < 0x1e) {
            *(signed char *)(*state + 0x1c7) = 0x10;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        if (func_ov227_020d0e98(node, dist) != 0) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov227_020d2568(node, state[0x16]);
}
