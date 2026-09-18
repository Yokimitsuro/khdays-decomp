/* Facing check of the ov144 enemy (and its byte-identical twin): once the +0x30 yaw is within
 * 0x1ac of the +0x34 target yaw (angle between them through the cosine of the difference), the
 * actor's +0x3f4 flag is raised and the tick hands off to cd5b8. */
extern int func_0203cd20(int c);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov145_020cf3d4(int *node);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov145_020cf63c(int *node)
{
    int *state = (int *)node[1];
    unsigned int ic = ANG2IDX(state[0xc]);
    unsigned int it = ANG2IDX(state[0xd]);
    int cosT = data_0203d210[it * 2];
    int cosC = data_0203d210[ic * 2];
    int sinT = data_0203d210[it * 2 + 1];
    int sinC = data_0203d210[ic * 2 + 1];
    int ang = func_0203cd20(FX_MUL(cosT, cosC) + FX_MUL(sinT, sinC));

    if (ang < 0) {
        ang = -ang;
    }
    if (ang >= 0x1ac) {
        return;
    }
    *(int *)(*state + 0x3f4) = 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov145_020cf3d4);
}
