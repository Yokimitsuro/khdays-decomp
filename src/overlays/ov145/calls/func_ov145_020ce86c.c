extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int y);

void func_ov145_020ce86c(int *state) {
    int local[3];
    if (state[0x13] != 0) {
        VEC_Subtract((void *)(state + 6), (void *)(*state + 0x74), local);
    } else {
        if (state[1] == 0) return;
        VEC_Subtract((void *)(state[1] + 0x74), (void *)(*state + 0x74), local);
    }
    state[0xd] = func_020050b4(local[0], local[2]);
}
