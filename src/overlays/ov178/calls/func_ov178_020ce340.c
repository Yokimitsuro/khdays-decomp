extern void func_0203c634();
extern void func_ov178_020ce740();
extern void func_ov107_020c9264();
extern void func_ov178_020ce3b4(void);
void func_ov178_020ce340(int node) {
    int *s = *(int **)(node + 4);
    func_ov178_020ce740(*(int *)(*s + 0x3ac));
    func_ov107_020c9264(*s, 3, 0);
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov178_020ce3b4);
}
