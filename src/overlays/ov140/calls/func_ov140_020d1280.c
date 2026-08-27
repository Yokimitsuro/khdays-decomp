extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov140_020d1324(void);

struct sbit1 { unsigned char b : 1; };

void func_ov140_020d1280(int *node) {
    int *state = (int *)node[1];
    int s = *state;
    if (((struct sbit1 *)(s + 0x17a))->b == 0 && ((struct sbit1 *)(s + 0x17c))->b == 0)
        return;
    {
        unsigned short hw60 = *(unsigned short *)(s + 0x60);
        *(unsigned short *)(s + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }
    func_ov107_020c9ee8(*(int *)(*state + 0x390), 2, 0);
    func_ov107_020c9264(*state, 7, 0);
    func_ov107_020c5af8(*state, 0x11f, 6, state[0x13]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov140_020d1324);
}
