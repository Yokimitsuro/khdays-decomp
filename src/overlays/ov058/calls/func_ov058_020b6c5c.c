extern void func_ov022_02091228(int v);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov058_020b6c5c(char *base) {
    func_ov022_02091228(*(int *)(base + 0x2644));
    NNSi_FndFreeFromDefaultHeap(*(void **)(base + 0x2644));
}
