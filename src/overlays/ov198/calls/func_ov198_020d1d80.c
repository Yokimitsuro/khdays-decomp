struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov198_020d1e28(void);
extern void func_ov198_020d1f04(void);
extern void func_ov198_020d1ea0(void);
void func_ov198_020d1d80(int *node) {
    int *state = (int *)node[1];
    state[1] = *state + 0xb0;
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = 0xff;
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    func_0203c634(node, 0, func_ov198_020d1e28);
    func_0203c634(node, 1, func_ov198_020d1f04);
    func_0203c634(node, 2, func_ov198_020d1ea0);
}
