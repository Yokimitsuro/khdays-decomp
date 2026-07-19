extern void func_ov183_020d0344(int a, int b, int c);
extern int func_02023eb4(int range);
extern void func_0203c634(int *self, int idx, void *cb);

void func_ov183_020d1a34(int *self) {
    int *p = (int *)self[0];
    int *s = (int *)self[1];
    int t = s[7] + p[0xb];
    s[7] = t;
    if (t >= 0x555 && t < 0x800 && *(unsigned char *)((char *)s + 0x50) == 0) {
        *(unsigned char *)((char *)s + 0x50) = 1;
        func_ov183_020d0344((int)s, 0, 1);
    }
    if (*(unsigned char *)s[3] != 0) return;
    {
        int lo = *(int *)(s[0] + 0x224);
        int d = *(int *)(s[0] + 0x228) - lo;
        if (d < 0) d = -d;
        s[0x1d] = lo + func_02023eb4(d + 1);
    }
    *(signed char *)(s[0] + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
}
