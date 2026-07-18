extern int func_02023eb4(int range);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov189_020d1164(void);

void func_ov189_020d10f8(int self) {
    int *s = *(int **)(self + 4);
    if (s[7] <= 0) {
        int lo = *(int *)(s[0] + 0x224);
        int d = *(int *)(s[0] + 0x228) - lo;
        if (d < 0) d = -d;
        s[7] = lo + func_02023eb4(d + 1);
    }
    func_ov107_020c9264(s[0], 2, 1);
    s[6] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), (void *)&func_ov189_020d1164);
}
