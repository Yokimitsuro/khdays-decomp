/* Lunge tick of the ov259 actor: it keeps turning from the +0x10 point to the +0x2c goal (+0x78 /
 * +0x7c heading) and the +0x14 drift becomes the heading's unit vector with the goal's normalised
 * height. While the goal is farther than 0.5 (020cddbc) and the actor is airborne on neither flag of
 * +0x17a the drift scales by 0.4375; otherwise +0x60 stops it, and a stopped actor's drift clears.
 * Once the partner holds no queued move the node moves on to 020cf474. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct Flag17a { u8 b0 : 1; u8 b1 : 1; };

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int y);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern int func_ov259_020cddbc(int *node, Vec3 goal);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cf474(void);
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov259_020cf324(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    Vec3 n;

    VEC_Subtract((Vec3 *)(state + 0xb), (Vec3 *)state[4], &d);
    state[0x1e] = state[0x1f] = func_020050b4(d.x, d.z);
    func_01ff8d18(&d, &n);
    {
        int idx = ANG2IDX(state[0x1e]);

        int y = n.y;
        state[5] = data_0203d210[idx * 2];
        state[6] = y;
        state[7] = data_0203d210[idx * 2 + 1];
    }
    if (func_ov259_020cddbc(node, *(Vec3 *)(state + 0xb)) > 0x800 &&
        !((struct Flag17a *)(*state + 0x17a))->b0 && !((struct Flag17a *)(*state + 0x17a))->b1) {
        func_01ffa724(0x700, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
    } else {
        state[0x18] = 1;
    }
    if (state[0x18] != 0) {
        *(Vec3 *)(state + 5) = data_02041dc8;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cf474);
}
