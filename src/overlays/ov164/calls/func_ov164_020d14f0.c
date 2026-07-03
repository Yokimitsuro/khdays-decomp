extern void func_ov107_020c9ee8();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov164_020d155c(void);
void func_ov164_020d14f0(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    func_ov107_020c9ee8(*(int *)(*state + 0x3c8), 0, 0);
    func_ov107_020c9264(*state, 4, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov164_020d155c);
}
