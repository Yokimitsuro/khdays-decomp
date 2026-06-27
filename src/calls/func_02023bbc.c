extern void WM_EndKeySharing_0x02023ad0(int *arg);

int func_02023bbc(int *p) {
    int result = 0;
    if (p[5] == -2) {
        if (p[0] & 1) WM_EndKeySharing_0x02023ad0(p);
        result = 1;
    }
    return result;
}
