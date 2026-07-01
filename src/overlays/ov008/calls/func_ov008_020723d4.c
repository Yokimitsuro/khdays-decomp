extern int func_0201ef9c();
extern int func_02011988();
extern int NNSi_FndFreeFromDefaultHeap();

int func_ov008_020723d4(int a0, int (*fp)()) {
    int *local;
    int *r4;
    int ret;

    r4 = (int *)func_0201ef9c(a0, 0xe);
    func_02011988(r4, &local);
    ret = fp(local[5], 0, local[4]);
    if (r4 == 0) {
        return ret;
    }
    return NNSi_FndFreeFromDefaultHeap(r4);
}
