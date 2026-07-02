extern void func_0203c634();
extern void func_ov295_020d3db4(void);
void func_ov295_020d3d74(int node) {
    int *s = *(int **)(node + 4);
    unsigned int h = *(unsigned short *)(*s + 0x60);
    *(unsigned short *)(*s + 0x60) = (h & ~0xff00) | (((((h << 0x10) >> 0x18) | 0xde) << 0x18) >> 0x10);
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov295_020d3db4);
}
