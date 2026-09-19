/* func_ov253_020d3de0 -- hit filter of the +0x214 sub-state: a hit with low bit 4, while the
 * +0x44 latch is clear, flips the +0x14 direction, latches +0x44 and clears +0x24. Returns 1
 * when handled. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);

int func_ov253_020d3de0(int self, int a, unsigned int *hit) {
    int *state = *(int **)(self + 0x214);

    if (((unsigned short)*hit & 0x10) != 0) {
        if (state[0x11] != 0) {
            return 0;
        }
        func_01ffa724(-0x1000, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
        state[0x11] = 1;
        state[9] = 0;
        return 1;
    }
    return 0;
}
