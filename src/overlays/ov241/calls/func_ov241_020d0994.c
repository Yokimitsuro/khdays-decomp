extern void func_0203c634();
extern void func_ov241_020d09c8(void);
void func_ov241_020d0994(int node) {
    int *a = *(int **)node;
    int *b = *(int **)(node + 4);
    int diff = b[0xb] - a[0xb];
    b[0xb] = diff;
    if (diff > 0) return;
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov241_020d09c8);
}
