/*
 * [nonmatching: walking-base/counter r4<->r5 coloring swap (p vs i); structurally byte-identical]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation / scheduling. Left uncarved (byte-exact in the blob).
 */
extern int func_ov022_02083f0c(void);
extern void func_ov002_02050e64(void);
extern void func_ov002_0205126c(int arg0);
extern void func_ov000_0204cac0(int arg0, int arg1);
extern int data_ov022_020b2e74;

void func_ov022_02086e80(int arg0) {
    int i = 0;
    int p = *(int *)&data_ov022_020b2e74;
    int g = func_ov022_02083f0c();
    func_ov002_02050e64();
    do {
        if (i < arg0) {
            if ((unsigned int)(*(unsigned char *)(p + 0x2a) << 0x1b) >> 0x1b) {
                func_ov002_0205126c(p);
            }
        }
        i = i + 1;
        p = p + 0x30;
    } while (i < 4);
    func_ov000_0204cac0(g, 0);
}
