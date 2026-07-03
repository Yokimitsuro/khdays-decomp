extern void func_ov107_020c9264();
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int z);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov131_020cd7f0(void);

void func_ov131_020cd780(char *obj) {
    int *state = *(int **)(obj + 4);
    int v[3];
    func_ov107_020c9264(*state, 3, 0);
    if (state[0xe] != 0) {
        int a;
        VEC_Subtract((void *)(state[0xe] + 0x190), (void *)(*state + 0xb0), v);
        a = func_020050b4(v[0], v[2]);
        state[4] = a;
        state[3] = a;
    }
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov131_020cd7f0);
}
