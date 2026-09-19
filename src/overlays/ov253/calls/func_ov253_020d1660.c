/* func_ov253_020d1660 -- carried item climb: the +0x384 owner's chain picked by the +0x388
 * count plus three minus its +0x450 side, modulo four, supplies the +8 / +0x14 endpoints at
 * the +0x24 joint index and the next one; the +0x20 timer runs up and its ratio over 0.25
 * (clamped to 1.0) places the +4 item along the segment at scale 2.0, turned to face it about
 * data_02042264, with the item's +0x70 grey level rising with the index (bit 1 of +0x5c
 * cleared); once complete the item sits at the far end, the timer restarts and the index
 * advances -- at four the node is released (0203c640). */
typedef struct { int x, y, z; } Vec3;
struct Ov253Joints { int cur[1]; int next[3]; };

extern int FX_Inv(int num, int den);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202ed60(void *rotation, const Vec3 *from, const Vec3 *to);
extern void func_0203ca30(void *srt, const Vec3 *translation);
extern void func_0203ca9c(void *srt, int scale);
extern void func_0203c9d0(void *srt, const void *rotation);
extern void func_0203c640(int *node);
extern const Vec3 data_02042264;

static inline int Ov253_Grey(int v) {
    return v | (v << 5) | (v << 10);
}

void func_ov253_020d1660(int *node) {
    int *state = (int *)node[1];
    int *anchors[4];
    Vec3 pos;
    Vec3 dir;
    int rot[4];
    int t;
    int len;
    int idx;
    int *chain;
    int owner = *(int *)(*state + 0x384);

    state[8] += *(int *)(node[0] + 0x2c);
    t = FX_Inv(state[8], 0x400);
    if (t > 0x1000) {
        t = 0x1000;
    }
    *(int *)(state[1] + 0x5c) &= ~2;
    *(unsigned short *)(state[1] + 0x70) = Ov253_Grey(((t << 3) + (state[9] << 15)) >> 12);
    anchors[3] = (int *)(owner + 0x3ac);
    anchors[0] = (int *)(owner + 0x3f4);
    anchors[1] = (int *)(owner + 0x418);
    anchors[2] = (int *)(owner + 0x3d0);
    idx = (*(int *)(*state + 0x388) + (3 - *(signed char *)(owner + 0x400 + 0x50))) % 4;
    chain = anchors[idx];
    *(Vec3 *)(state + 2) = *(Vec3 *)(chain[state[9]] + 0x14);
    *(Vec3 *)(state + 5) = *(Vec3 *)(((struct Ov253Joints *)chain)->next[state[9]] + 0x14);
    VEC_Subtract((Vec3 *)(state + 5), (Vec3 *)(state + 2), &dir);
    len = func_01ff8d18(&dir, &dir);
    func_01ffa724((int)(((long long)len * t + 0x800) >> 12), &dir, &pos);
    VEC_Add((Vec3 *)(state + 2), &pos, &pos);
    func_0202ed60(rot, &data_02042264, &dir);
    func_0203ca30((void *)(state[1] + 0x30), &pos);
    func_0203ca9c((void *)(state[1] + 0x30), 0x2000);
    func_0203c9d0((void *)(state[1] + 0x30), rot);
    if (t < 0x1000) {
        return;
    }
    func_0203ca30((void *)(state[1] + 0x30), (Vec3 *)(state + 5));
    state[8] = 0;
    state[9] += 1;
    if (state[9] != 4) {
        return;
    }
    func_0203c640(node);
}
