extern void func_0202a7dc(int arg0);
extern void WM_EndKeySharing_0x02023ad0(int arg0);
extern void func_ov022_02092e2c(unsigned char *arg0);

void func_ov022_02092e4c(unsigned char *arg0, int arg1, int arg2, int arg3) {
    int f = *arg0;
    if ((f & 1) != 0) {
        if ((f & 4) != 0) {
            int i = 0;
            int p = (int)arg0 + 4;
            do {
                func_0202a7dc(p);
                i = i + 1;
                p = p + 0x108;
            } while (i < 9);
            if (*(int *)((char *)arg0 + 0x94c) != 0) {
                WM_EndKeySharing_0x02023ad0(*(int *)((char *)arg0 + 0x94c));
            }
        }
        func_ov022_02092e2c(arg0);
    }
}
