extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov239_020cc9f0(int *node, int arg1, int arg2, int arg3, void *next) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, arg1, arg3);
    func_ov107_020c9ee8(*(int *)(*state + 0x398), arg2, arg3);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), next);
}
