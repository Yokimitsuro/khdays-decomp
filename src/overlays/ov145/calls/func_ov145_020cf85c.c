struct row3d4 { char _pad[0x3d4]; int f; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov145_020cf8b4(void);

void func_ov145_020cf85c(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)(*(int *)(*state + 0x384) + 0xad) != 0) return;
    func_ov107_020c9264(*state, 4, 1);
    state[0xe] = ((struct row3d4 *)((int *)*state + state[0x12]))->f;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov145_020cf8b4);
}
