struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov188_020cf818(void);

void func_ov188_020cf79c(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 5, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3c0), 0, 0);
    { unsigned short *p = (unsigned short *)(*state + 0x60); unsigned int u = *p;
      *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10)); }
    state[6] = 0;
    *(unsigned char *)((char *)state + 0x3c) = 0;
    *(unsigned char *)((char *)state + 0x3d) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov188_020cf818);
}
