/* Retreat entry of the ov297 enemy: spawns effect 0 and fires reaction 0x176 mode 4 at the +8
 * point, then draws one of the overlay's 10 retreat points of the set chosen by +0x91 at random until one is found that
 * was not used in the last four (+0x64 ring) and lies within 0x18000 of the actor (up to 100
 * far draws); the pick is recorded in the ring, the +0x10 velocity is zeroed, the actor is
 * placed at the point, the +0x38 timer resets, sub-state 2 is requested and the state ends. */
typedef struct { int x, y, z; } VecFx32;
struct PointTable { VecFx32 p[2][10]; };

extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int d);
extern void func_ov107_020c5af8(int actor, int a, int b, void *at);
extern int func_02023eb4(int range);
extern int func_ov297_020d4200(int *node, VecFx32 v);
extern void func_ov107_020c5c54(int actor, VecFx32 *pos);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct PointTable data_ov297_020d56b4;
extern const VecFx32 data_02041dc8;

void func_ov297_020d5394(int *node)
{
    int *state = (int *)node[1];
    struct PointTable pts;
    VecFx32 pick;
    int k;
    int tries;
    int done;
    int i;
    const VecFx32 *p;
    int set;

    tries = 0;
    set = 0;
    pts = data_ov297_020d56b4;
    if (*(signed char *)((char *)state + 0x91) != 0) {
        if (*(signed char *)((char *)state + 0x91) == 1) {
            set = 1;
        }
    } else {
        set = 0;
    }
    func_ov107_020c0b90(*state, 0, *(VecFx32 *)state[2], 0);
    func_ov107_020c5af8(*state, 0x176, 4, (void *)state[2]);
    p = pts.p[set];
    do {
        done = 1;
        k = func_02023eb4(0xa);
        for (i = 0; i < 4; i++) {
            if (k == state[0x19 + i]) {
                done = 0;
            }
        }
        if (func_ov297_020d4200(node, p[k]) > 0x18000) {
            tries++;
            if (tries < 100) {
                done = 0;
            } else {
                done = 1;
            }
        }
    } while (!done);
    pick.x = pts.p[set][k].x;
    pick.y = pts.p[set][k].y;
    pick.z = pts.p[set][k].z;
    ((int *)((char *)state + 0x64))[state[0x18]] = k;
    state[0x18]++;
    *(VecFx32 *)(state + 4) = data_02041dc8;
    func_ov107_020c5c54(*state, &pick);
    state[0xe] = 0;
    state[0x1f] = 0;
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
