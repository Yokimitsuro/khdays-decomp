/* func_ov253_020d1248 -- carried item lift: the +8 / +0x14 endpoints follow the +0x39c and +0x398
 * joints' anchors; the +0x20 timer runs up and its ratio over 0.333 (clamped to 1.0) places the
 * +4 item along the segment, scaled by twice the ratio and turned to face the segment about
 * data_02042264; once complete the item sits at the far end with scale 2.0, the timer restarts,
 * the +0x24 hop count becomes 2 and the node moves to 020d139c. */
typedef struct { int x, y, z; } Vec3;

extern int FX_Inv(int num, int den);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202ed60(void *rotation, const Vec3 *from, const Vec3 *to);
extern void func_0203ca9c(void *srt, int scale);
extern void func_0203ca30(void *srt, const Vec3 *translation);
extern void func_0203c9d0(void *srt, const void *rotation);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042264;
extern void func_ov253_020d139c(void);

void func_ov253_020d1248(int *node) {
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 pos;
    int rot[4];
    int t;
    int len;

    *(Vec3 *)(state + 2) = *(Vec3 *)(*(int *)(*state + 0x39c) + 0x14);
    *(Vec3 *)(state + 5) = *(Vec3 *)(*(int *)(*state + 0x398) + 0x14);
    state[8] += *(int *)(node[0] + 0x2c);
    t = FX_Inv(state[8], 0x555);
    if (t > 0x1000) {
        t = 0x1000;
    }
    VEC_Subtract((Vec3 *)(state + 5), (Vec3 *)(state + 2), &dir);
    len = func_01ff8d18(&dir, &dir);
    func_01ffa724((int)(((long long)len * t + 0x800) >> 12), &dir, &pos);
    VEC_Add((Vec3 *)(state + 2), &pos, &pos);
    func_0202ed60(rot, &data_02042264, &dir);
    func_0203ca9c((void *)(state[1] + 0x30), t * 2);
    func_0203ca30((void *)(state[1] + 0x30), &pos);
    func_0203c9d0((void *)(state[1] + 0x30), rot);
    if (t < 0x1000) {
        return;
    }
    func_0203ca30((void *)(state[1] + 0x30), (Vec3 *)(state + 5));
    func_0203ca9c((void *)(state[1] + 0x30), 0x2000);
    state[8] = 0;
    state[9] = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d139c);
}
