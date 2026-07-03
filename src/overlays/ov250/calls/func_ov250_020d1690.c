struct v3 { int a, b, c; };
extern void func_01ffa724();
extern int VEC_Mag();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov250_020d16f4(void);
void func_ov250_020d1690(int *node) {
    int *state = (int *)node[1];
    *(struct v3 *)(state + 0x15) = *(struct v3 *)(state + 0x18);
    func_01ffa724(0xb00, state + 0x18, state + 0x18);
    if (VEC_Mag(state + 0x18) >= 0x10) return;
    func_ov107_020c9264(*state, 10, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov250_020d16f4);
}
