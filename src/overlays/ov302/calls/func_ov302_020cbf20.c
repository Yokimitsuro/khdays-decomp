extern int func_020200c8();
extern int func_020200e4();
extern int NNSi_FndAllocFromDefaultExpHeap();

int func_ov302_020cbf20(int *a, char *b) {
    char *p;
    int n;

    n = (func_020200c8(b) + 1) * 2;
    p = (char *)NNSi_FndAllocFromDefaultExpHeap(n);
    func_020200e4(p, b);
    if (a) {
        *a = (int)(b + n);
    }
    return (int)p;
}
