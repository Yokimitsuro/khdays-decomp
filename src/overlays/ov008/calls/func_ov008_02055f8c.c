extern int NNSi_FndFreeFromDefaultHeap();

struct S {
    char pad[0x3c];
    int f3c;
    int f40;
    int f44;
    int f48;
};

void func_ov008_02055f8c(struct S *p)
{
    if (p->f3c) {
        NNSi_FndFreeFromDefaultHeap();
        p->f3c = 0;
    }
    if (p->f40) {
        NNSi_FndFreeFromDefaultHeap();
        p->f40 = 0;
    }
    if (p->f44) {
        NNSi_FndFreeFromDefaultHeap();
        p->f44 = 0;
    }
    if (p->f48) {
        NNSi_FndFreeFromDefaultHeap();
        p->f48 = 0;
    }
}
