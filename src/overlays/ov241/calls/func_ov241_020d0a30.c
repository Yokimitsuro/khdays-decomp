extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov241_020d0a80(void);

void func_ov241_020d0a30(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 1, 1);
    func_ov107_020c9ee8(*(int *)(*state + 0x39c), 0, 1);
    *(unsigned char *)((char *)state + 0x40) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov241_020d0a80);
}
