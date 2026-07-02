extern void func_0203c634();
extern void func_ov180_020d5fc0();
extern void func_ov107_020c9264();
extern void func_ov180_020d5c34(void);
void func_ov180_020d5bc0(int node) {
    int *s = *(int **)(node + 4);
    func_ov180_020d5fc0(*(int *)(*s + 0x3ac));
    func_ov107_020c9264(*s, 3, 0);
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov180_020d5c34);
}
