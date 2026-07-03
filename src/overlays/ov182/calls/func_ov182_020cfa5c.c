struct v3 { int a, b, c; };
extern void func_01ffa724();
extern int func_01ff8cb8();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov182_020cfac0(void);
void func_ov182_020cfa5c(int *node) {
    int *state = (int *)node[1];
    *(struct v3 *)(state + 0x15) = *(struct v3 *)(state + 0x18);
    func_01ffa724(0xb00, state + 0x18, state + 0x18);
    if (func_01ff8cb8(state + 0x18) >= 0x10) return;
    func_ov107_020c9264(*state, 10, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov182_020cfac0);
}
