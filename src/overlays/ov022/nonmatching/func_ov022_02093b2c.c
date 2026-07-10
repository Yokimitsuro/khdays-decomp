/*
 * [nonmatching: walking bases a/b and counter i r5<->r6 coloring swap; structurally byte-identical]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation / scheduling. Left uncarved (byte-exact in the blob).
 */
extern void func_0202a7dc(int arg0);
extern void func_0202a440(int arg0);

void func_ov022_02093b2c(unsigned char *arg0, int arg1, int arg2, int arg3) {
    if ((*arg0 & 1) != 0) {
        int a;
        int b;
        int i;
        i = 0;
        a = (int)arg0 + 0x20;
        b = (int)arg0 + 0x440;
        do {
            func_0202a7dc(a);
            func_0202a440(b);
            i = i + 1;
            a = a + 0x108;
            b = b + 0x24;
        } while (i < 4);
    }
    *arg0 = 0;
}
