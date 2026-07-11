extern void func_ov022_02091228(void *);
extern void NNSi_FndFreeFromDefaultHeap(void *);

void func_ov072_020b94f8(char *obj) {
    func_ov022_02091228(*(void **)(obj + 0x2644));
    func_ov022_02091228((char *)*(void **)(obj + 0x2644) + 0x30);
    NNSi_FndFreeFromDefaultHeap(*(void **)(obj + 0x2644));
}
