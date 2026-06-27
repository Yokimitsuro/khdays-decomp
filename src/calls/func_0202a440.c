extern int WM_EndKeySharing_0x0201696c();
extern void func_0201f5ac(int a);
extern void func_0201f6b0(void);
extern void NNSi_FndFreeFromDefaultHeap(int a);
extern int NNSi_FndGetAllocatorForDefaultHeap(int a);

void func_0202a440(int *p) {
    int i, j;
    int last = 0;
    for (i = 4; i >= 0; i--) {
        for (j = ((short *)p)[i] - 1; j >= 0; j--) {
            WM_EndKeySharing_0x0201696c(NNSi_FndGetAllocatorForDefaultHeap(0), ((int *)p[i + 4])[j]);
        }
        if (p[i + 4]) last = p[i + 4];
    }
    if (last) NNSi_FndFreeFromDefaultHeap(last);
    if (p[3]) {
        func_0201f6b0();
        func_0201f5ac(p[3]);
    }
    p[3] = 0;
}
