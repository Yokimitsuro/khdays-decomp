/* Raise the "alert" pose (hw60 high-byte bit 0x80) and register the alert think callback, but only
 * while the flag at *node[2] is clear. */
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov273_020d27bc(void);

void func_ov273_020d276c(int param_1) {
    int *node = *(int **)(param_1 + 4);
    unsigned short hw60;
    if (*(unsigned char *)node[2] != 0) {
        return;
    }
    hw60 = *(unsigned short *)(*node + 0x60);
    *(unsigned short *)(*node + 0x60) =
        (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov273_020d27bc);
}
