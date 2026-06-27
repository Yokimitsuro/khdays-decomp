extern void NNSi_FndInitHeapHead(void *hh, unsigned magic, void *start, void *end, int opt);

void *NNSi_FndInitExpHeap(void *hh_void, void *end, int opt) {
    char *hh = (char*)hh_void;
    NNSi_FndInitHeapHead(hh, 0x46524D48, hh + 0x30, end, opt);
    *(int*)(hh + 0x24) = *(int*)(hh + 0x18);
    *(int*)(hh + 0x28) = *(int*)(hh + 0x1c);
    *(int*)(hh + 0x2c) = 0;
    return hh;
}
