/* For each variable-stride record, build a sprite via 0205657c (kind-mapped priority) and place it via 02056884. */
extern int func_ov000_0205657c(int self, int a, int b, int c, int d, int e, int f, int prio);
extern void func_ov000_02056884(int self, int handle, int x, int y);
extern unsigned char data_ov000_0205a900;
extern unsigned char data_ov000_0205a8fc;
void func_ov000_02055ee4(int param_1, int param_2) {
    unsigned int n = *(unsigned int *)param_2;
    int p = param_2 + 4;
    unsigned int i;
    for (i = 0; i < n; i++) {
        unsigned int kind = *(unsigned short *)(p + 0x14);
        unsigned char prio = kind >= 0xa ? (&data_ov000_0205a900)[kind - 0xa]
                                          : (&data_ov000_0205a8fc)[kind];
        int handle = func_ov000_0205657c(param_1, *(unsigned short *)(p + 6),
            *(unsigned short *)(p + 4), *(unsigned short *)(p + 0xc),
            *(unsigned short *)(p + 0xe), *(short *)(p + 0x10),
            *(short *)(p + 0x12), prio);
        func_ov000_02056884(param_1, handle, *(short *)(p + 8), *(short *)(p + 0xa));
        p += *(int *)p;
    }
}
