extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov145_020cf3d4(void);

void func_ov145_020cf37c(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)(*(int *)(*state + 0x384) + 0xad) != 0) return;
    func_ov107_020c9264(*state, 7, 1);
    func_ov107_020c9ee8(*(int *)(*state + 0x394), 1, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov145_020cf3d4);
}
