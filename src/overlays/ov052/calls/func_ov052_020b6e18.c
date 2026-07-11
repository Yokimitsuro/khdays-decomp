extern void func_ov022_02091228(void *);
extern void NNSi_FndFreeFromDefaultHeap(void *);

void func_ov052_020b6e18(char *obj) {
    func_ov022_02091228(*(void **)(obj + 0x2644));
    func_ov022_02091228((char *)*(void **)(obj + 0x2644) + 0x30);
    NNSi_FndFreeFromDefaultHeap(*(void **)(obj + 0x2644));
}
