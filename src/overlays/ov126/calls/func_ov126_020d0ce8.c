/* Hover tick of the ov125 enemy: the +0x3c counter is reseeded with 3 times the owner's +0x2c
 * rate (30/10) and the +0x38 phase advances by 30 x rate, wrapping at 120.0; its sine
 * (FX_Mul by 0x6488, /120, RadToIdx into data_0203d210) halved plus 2.0 is the hover height,
 * eased into +0xc by a tenth while the +0x13c height is valid. Then the target is re-acquired
 * (020cab14) into +4; with one, the gap between the two +0x74 positions less both radii decides
 * whether to stay or, within the owner's reach (+0x2d8), queue pose 4. */
struct v3 { int x, y, z; };

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}
static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

extern int  func_ov107_020cab14(int obj, int flag);
extern void VEC_Subtract(const void *a, const void *b, void *out);
extern int  func_01ff8d18(const void *a, void *out);
extern void func_0203c634(int self, int idx, int cb);
extern short data_0203d210[];

void func_ov126_020d0ce8(int *self) {
    int owner;
    int *state = (int *)self[1];
    struct v3 dir;
    int target;
    int actor;
    int d;
    int zero = 0;

    owner = *state;
    state[0xf] = *(int *)(self[0] + 0x2c) * 30 / 10;
    state[0xe] += *(int *)(self[0] + 0x2c) * 30;
    if (state[0xe] >= 0x78000) state[0xe] = 0;
    {
        unsigned short idx = FX_RadToIdx(FX_Mul(state[0xe], 0x6488) / 120);
        int h = data_0203d210[(idx >> 4) << 1] / 2 + 0x2000;
        if (*(int *)(owner + 0x13c) != zero - 0x80000001) {
            state[3] += (h - *(int *)(owner + 0x13c)) / 10;
        }
    }
    state[1] = func_ov107_020cab14(*state, 0);
    if (state[1] == 0) {
        return;
    }
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[9], &dir);
    target = state[1];
    actor = *state;
    d = func_01ff8d18(&dir, &dir) - *(int *)(target + 0x80) - *(int *)(actor + 0x80);
    if (d > *(int *)(*state + 0x2d8)) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
