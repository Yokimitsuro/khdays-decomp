/* Turns the heading toward the stored point, or toward the target when there is no point. */

extern void VEC_Subtract(void *a, void *b, void *out);
extern short FX_Atan2(int x, int y);

void Ov145_AimYawToTarget(int *state) {
    int local[3];
    if (state[0x13] != 0) {
        VEC_Subtract((void *)(state + 6), (void *)(*state + 0x74), local);
    } else {
        if (state[1] == 0) return;
        VEC_Subtract((void *)(state[1] + 0x74), (void *)(*state + 0x74), local);
    }
    state[0xd] = FX_Atan2(local[0], local[2]);
}
