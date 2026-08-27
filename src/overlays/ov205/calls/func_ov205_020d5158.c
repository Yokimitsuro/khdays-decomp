extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov205_020d51e4(void);

struct sbit1 { unsigned char b : 1; };

void func_ov205_020d5158(int *node) {
    int *state = (int *)node[1];
    int s = *state;
    if (((struct sbit1 *)(s + 0x17a))->b == 0 && ((struct sbit1 *)(s + 0x17c))->b == 0)
        return;
    func_ov107_020c9ee8(*(int *)(s + 0x390), 3, 0);
    func_ov107_020c9264(*state, 8, 0);
    func_ov107_020c5af8(*state, 0x132, 7, state[8]);
    *((char *)state + 0x44) = 0;
    state[0xb] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov205_020d51e4);
}
