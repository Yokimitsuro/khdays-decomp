extern void func_02030d10(int arg0);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2ea8;

void func_ov022_02091228(int arg0) {
    int c = *(int *)&data_ov022_020b2ea8 - 1;
    *(int *)&data_ov022_020b2ea8 = c;
    if (c == 0) func_02030d10(9);
    (*(void (**)(int))(arg0 + 0x28))(arg0);
    if (*(int *)(arg0 + 0x10) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(arg0 + 0x10));
    }
}
