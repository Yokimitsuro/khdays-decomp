typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_ov107_020c9ee8(int obj, int a, int b);
extern void func_0203c634(void *node, int idx, void *next);
extern void func_ov122_020d1834(void);

void func_ov122_020d17c0(int *node) {
    int *state = (int *)node[1];
    state[0xb] -= 0x100;
    *(Vec3 *)(state + 7) = *(Vec3 *)(state + 10);
    if (((unsigned int)(*(unsigned char *)(*state + 0x17a) << 0x1f) >> 0x1f) == 0) return;
    func_ov107_020c9264(*state, 8, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a0), 2, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov122_020d1834);
}
