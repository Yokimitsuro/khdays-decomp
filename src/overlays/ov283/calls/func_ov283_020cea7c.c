/* Swipe pick of the ov283 actor: +0x5c is 0.56; with a target (+0xc) both headings (+0x38, +0x40)
 * turn toward it and it counts as in front when it lies ahead of the old +0x38 heading. A front target
 * gets pose 5 or 6, otherwise 7 or 8 (random), and the node moves on to 020cebb4. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern int func_020050b4(int x, int z);
extern int func_02023eb4(int bound);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov283_020cebb4(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov283_020cea7c(int *node)
{
    int *state = (int *)node[1];
    Vec3 fwd;
    Vec3 d;
    int front;
    int actor;

    state[0x17] = 0x900;
    front = 0;
    if (state[3] != 0) {
        {
            int idx = ANG2IDX(state[0xe]) * 2;

            fwd.y = 0;
            fwd.x = data_0203d210[idx];
            fwd.z = data_0203d210[idx + 1];
        }
        VEC_Subtract((Vec3 *)(state[3] + 0x74), (Vec3 *)(*state + 0x74), &d);
        func_01ff8d18(&d, &d);
        if (VEC_DotProduct(&fwd, &d) >= 0) {
            front = 1;
        }
        state[0xe] = state[0x10] = func_020050b4(d.x, d.z);
    }
    actor = *state;
    if (front) {
        func_ov107_020c9264(actor, func_02023eb4(2) + 5, 0);
    } else {
        func_ov107_020c9264(actor, func_02023eb4(2) + 7, 0);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020cebb4);
}
