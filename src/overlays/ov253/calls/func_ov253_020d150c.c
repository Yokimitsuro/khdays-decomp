/* func_ov253_020d150c -- carried item return: the +8 start follows the actor's +0x390 item
 * anchor and the +0x14 end one of the +0x384 owner's four part anchors (+0x3f4 / +0x418 /
 * +0x3d0 / +0x3ac) picked by the +0x388 count plus three minus the owner's +0x450 side, modulo
 * four; the +0x20 timer runs up and its ratio over 0.25 (clamped to 1.0) places the +4 item
 * along the segment; once complete the timer and hop count clear, the item sits at the end and
 * the node moves to 020d1660. */
typedef struct { int x, y, z; } Vec3;

extern int FX_Inv(int num, int den);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0203ca30(void *srt, const Vec3 *translation);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020d1660(void);

void func_ov253_020d150c(int *node) {
    int *state = (int *)node[1];
    int *anchors[4];
    Vec3 dir;
    Vec3 pos;
    int t;
    int len;
    int idx;
    int *chain;
    int owner = *(int *)(*state + 0x384);

    anchors[3] = (int *)(owner + 0x3ac);
    anchors[0] = (int *)(owner + 0x3f4);
    anchors[1] = (int *)(owner + 0x418);
    anchors[2] = (int *)(owner + 0x3d0);
    idx = (*(int *)(*state + 0x388) + (3 - *(signed char *)(owner + 0x400 + 0x50))) % 4;
    chain = anchors[idx];
    *(Vec3 *)(state + 2) = *(Vec3 *)(*(int *)(*state + 0x390) + 0x14);
    *(Vec3 *)(state + 5) = *(Vec3 *)(chain[0] + 0x14);
    state[8] += *(int *)(node[0] + 0x2c);
    t = FX_Inv(state[8], 0x400);
    if (t > 0x1000) {
        t = 0x1000;
    }
    VEC_Subtract((Vec3 *)(state + 5), (Vec3 *)(state + 2), &dir);
    len = func_01ff8d18(&dir, &dir);
    func_01ffa724((int)(((long long)len * t + 0x800) >> 12), &dir, &pos);
    VEC_Add((Vec3 *)(state + 2), &pos, &pos);
    func_0203ca30((void *)(state[1] + 0x30), &pos);
    if (t < 0x1000) {
        return;
    }
    state[8] = 0;
    state[9] = 0;
    func_0203ca30((void *)(state[1] + 0x30), (Vec3 *)(state + 5));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d1660);
}
