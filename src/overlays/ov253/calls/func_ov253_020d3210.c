/* func_ov253_020d3210 -- ring seed: clears the +0x18 radius, raises the +0xc height by 1.0 and
 * lays every ring entry (stride 0x38, count at the owner's +0x8c) on a circle: entry i sits at
 * the +8 / +0x10 centre plus radius times the sine / cosine of i * 2pi / count, at the +0xc
 * height, with kind 0x10; the +0x1c timer is armed with 0.25 and the node moves to 020d33d8. */
extern int func_02020400(int num, int den);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov253_020d33d8(void);

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}
static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void func_ov253_020d3210(int *node) {
    int *state = (int *)node[1];
    int i;
    char *entry;
    unsigned short idx;

    state[6] = 0;
    state[3] += 0x1000;
    for (i = 0; i < *(int *)(state[1] + 0x8c); i++) {
        entry = *(char **)(state[1] + 0x90) + i * 0x38;
        idx = FX_RadToIdx(func_02020400(i * 0x6488, *(int *)(state[1] + 0x8c)));
        *(int *)(entry + 0x2c) = state[2] + FX_Mul(data_0203d210[(idx >> 4) << 1], state[6]);
        *(int *)(entry + 0x30) = state[3];
        idx = FX_RadToIdx(func_02020400(i * 0x6488, *(int *)(state[1] + 0x8c)));
        *(int *)(entry + 0x34) = state[4] + FX_Mul(data_0203d210[((idx >> 4) << 1) + 1], state[6]);
        *(int *)entry = 0x10;
    }
    state[7] = 0x400;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d33d8);
}
