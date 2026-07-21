/* Enter the stagger state: set the hw60 high-byte "staggered" bit 2, cancel the current action
 * (mode 0x15), set the stagger sub-state byte (+0x55 = 2), clear the stagger timer (node[0xc]),
 * and register the think callback. */
extern void func_ov107_020c9264(int owner, int mode, int b);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov237_020cff0c(void);

void func_ov237_020cfea4(int param_1) {
    int *node = *(int **)(param_1 + 4);
    unsigned short hw60;
    hw60 = *(unsigned short *)(*node + 0x60);
    *(unsigned short *)(*node + 0x60) =
        (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 2) << 0x18) >> 0x10);
    func_ov107_020c9264(*node, 0x15, 0);
    *(char *)((char *)node + 0x55) = 2;
    node[0xc] = 0;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov237_020cff0c);
}
