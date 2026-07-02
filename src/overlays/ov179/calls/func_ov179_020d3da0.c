extern void func_0203c634();
extern void func_ov179_020d41a0();
extern void func_ov107_020c9264();
extern void func_ov179_020d3e14(void);
void func_ov179_020d3da0(int node) {
    int *s = *(int **)(node + 4);
    func_ov179_020d41a0(*(int *)(*s + 0x3ac));
    func_ov107_020c9264(*s, 3, 0);
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov179_020d3e14);
}
