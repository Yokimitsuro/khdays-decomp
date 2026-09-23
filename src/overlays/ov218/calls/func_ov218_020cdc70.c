/* Throw entry tick of the ov218 actor: the +0x28 velocity is its +0x3ac part's +0x2c vector turned by
 * the +0xc heading; once the partner holds no queued move pose 9 loops, +0x14 and +0x40 clear and the
 * node moves on to 020cdd44. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov218_020cdd44(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov218_020cdc70(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;

    {
        int idx = ANG2IDX(state[3]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x3ac) + 0x2c), &rot, (Vec3 *)(state + 0xa));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 9, 1);
    state[5] = 0;
    *((unsigned char *)state + 0x40) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov218_020cdd44);
}
