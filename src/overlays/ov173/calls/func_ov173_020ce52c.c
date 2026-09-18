/* Flight step 1 of the ov173 enemy (x2: ov173/174): the +0x20 velocity takes the +0x2c aim
 * scaled by 0xf00 (the aim itself is rescaled in place); without a +0x88 override the +0x50
 * phase advances 30 per frame (wrapping at 0x28000) and the vertical speed follows a sine of
 * phase * 0x6488 / 40, halved and scaled by 0x200. When the +4 sub-item's +0xad byte is clear
 * animation 7 plays and the state advances to func_ov173_020ce66c. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov173_020ce66c(void);

void func_ov173_020ce52c(int *node)
{
    int *state = (int *)node[1];
    int t;
    int idx;
    int s;

    *(Vec3 *)(state + 8) = *(Vec3 *)(state + 0xb);
    func_01ffa724(0xf00, (Vec3 *)(state + 0xb), (Vec3 *)(state + 0xb));
    if (state[0x22] == 0) {
        state[0x14] += *(int *)(*node + 0x2c) * 30;
        if (state[0x14] >= 0x28000) {
            state[0x14] = 0;
        }
        t = (int)(((long long)state[0x14] * 0x6488 + 0x800) >> 12) / 40;
        idx = (unsigned short)((0x28BE60DB9391LL * t + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
        s = data_0203d210[(idx >> 4) << 1] / 2;                                       /* FX_SinIdx / 2 */
        state[9] = (int)(((long long)s * 0x200 + 0x800) >> 12);
    }
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 7, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov173_020ce66c);
    }
}
