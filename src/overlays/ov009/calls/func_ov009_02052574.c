extern int NNSi_FndFreeFromDefaultHeap();

struct S {
    int unk0;
    int unk4;
    int unk8;
    int unkc;
};

void func_ov009_02052574(int a0, struct S *a1) {
    a1->unkc = 0;
    if (a1->unk4 != 0) {
        NNSi_FndFreeFromDefaultHeap(a1->unk4);
        a1->unk4 = 0;
    }
}
