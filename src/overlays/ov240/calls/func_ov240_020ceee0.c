/* Wander tick of the ov239 enemy: re-acquires the actor's +0x394 target (none requests
 * sub-state 2 and ends the state); a negative distance to it ends the state too, else the +0x14
 * velocity is the +0x398 part's +0x2c motion turned by the +0x10 yaw and the idle countdown may
 * end the state. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern int func_ov107_020cab14(int actor, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov240_020ce8e8(int *node);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern int func_ov240_020ce804(int *node, int dist);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov240_020ceee0(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    int dist;
    unsigned int idx;

    *(int *)(*state + 0x394) = func_ov107_020cab14(*state, 0);
    if (*(int *)(*state + 0x394) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    dist = func_ov240_020ce8e8(node);
    if (dist < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    idx = ANG2IDX(state[4]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x398) + 0x2c), &mtx, (Vec3 *)(state + 5));
    if (func_ov240_020ce804(node, dist) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
