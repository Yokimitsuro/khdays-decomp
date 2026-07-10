extern int func_02021980(void);
extern int func_020235d0(int query, int kind);
extern int func_020235e8(int query, int kind, int value);
extern int func_ov002_02078f60(void);

/* Record a high-water mark: pick the stat key for the current party slot
 * (0->0x140b, 1->0x1415, else 0x141f) and, if the live value exceeds the stored
 * one, write it back. Then refresh the ov002 summary. */
int func_ov019_0207fa40(void) {
    int slot = func_02021980();
    int cur = func_020235d0(0x208f, 0xa);
    int key;

    if (slot == 0) {
        key = 0x140b;
    } else if (slot == 1) {
        key = 0x1415;
    } else {
        key = 0x141f;
    }
    if (cur > func_020235d0(key, 0xa)) {
        func_020235e8(key, 0xa, (unsigned short)cur);
    }
    func_ov002_02078f60();
    return 1;
}
