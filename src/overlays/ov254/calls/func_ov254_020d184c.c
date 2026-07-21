/* Commit the guard reaction: raise both "guarding" bits (+0x1ae |= 3), set hw60 high-byte bit
 * pair 0xc (guard pose), and re-register the think callback. */
extern void func_0203c634(int self, int idx, int cb);

void func_ov254_020d184c(int param_1) {
    int *node = *(int **)(param_1 + 4);
    unsigned short hw60;
    *(unsigned short *)(*node + 0x1ae) |= 3;
    hw60 = *(unsigned short *)(*node + 0x60);
    *(unsigned short *)(*node + 0x60) =
        (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0xc) << 0x18) >> 0x10);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
}
