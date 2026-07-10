extern void func_0202a7dc(int arg0);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
void func_ov022_0208bb98(int arg0) {
    int i = 0;
    if (i < *(unsigned char *)(arg0 + 1)) {
        int e = i;
        do {
            func_0202a7dc(*(int *)(arg0 + 0x168) + e + 0x1c);
            i++;
            e += 0x150;
        } while (i < *(unsigned char *)(arg0 + 1));
    }
    NNSi_FndFreeFromDefaultHeap(*(int *)(arg0 + 0x168));
}
