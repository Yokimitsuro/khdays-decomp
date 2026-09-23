/* Approach tick of the ov227 enemy: the nearest target (020cab14) becomes the owner's +0x3e8; when
 * the tracking step (func_ov227_020d14bc) reports it lost, or the move chooser
 * (func_ov227_020d0e98) queues a move, the tick ends. Otherwise the +0x38 goal is the +8 point
 * pushed 100 steps along the flat direction and the tick hands over to func_ov227_020d2828. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int kind);
extern int func_ov227_020d14bc(int *node, Vec3 *dir);
extern int func_ov227_020d0e98(int *node, int dist);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov227_020d2828(int *node);

void func_ov227_020d2760(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int dist;

    *(int *)(*state + 0x3e8) = func_ov107_020cab14(*state, 0);
    dist = func_ov227_020d14bc(node, &dir);
    if (dist < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (func_ov227_020d0e98(node, dist) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *(Vec3 *)(state + 0xe) = *(Vec3 *)state[2];
    state[0xe] += dir.x * 100;
    state[0x10] += dir.z * 100;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov227_020d2828);
}
