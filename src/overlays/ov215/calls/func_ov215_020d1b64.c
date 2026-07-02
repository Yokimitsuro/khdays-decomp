extern void func_0203c634();
extern void func_ov107_020c9264();
extern void func_ov215_020d1ba8(void);
void func_ov215_020d1b64(int node) {
    int *s = *(int **)(node + 4);
    if (*(unsigned char *)(s[1] + 0xad) != 0) return;
    func_ov107_020c9264(*s, 7, 1);
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov215_020d1ba8);
}
