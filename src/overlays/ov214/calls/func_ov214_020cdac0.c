struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_ov107_020c9264();
extern void func_ov214_020cd138();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov214_020cdb34(void);

void func_ov214_020cdac0(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)(state[1] + 0xad) != 0) return;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    func_ov107_020c9264(*state, 4, 1);
    func_ov214_020cd138(*state, 1);
    func_0203c634(node, *(signed char *)(node + 8), func_ov214_020cdb34);
}
