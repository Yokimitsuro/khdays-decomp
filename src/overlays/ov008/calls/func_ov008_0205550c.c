extern void func_ov008_020559a8(void *);
extern void NNSi_FndFreeFromDefaultHeap(void *);
void func_ov008_0205550c(char *obj)
{
    func_ov008_020559a8(obj);
    if (*(void **)(obj + 0x14) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(obj + 0x14));
    }
    if (*(void **)(obj + 0x10) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(obj + 0x10));
    }
    if (*(void **)(obj + 0xc) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(obj + 0xc));
    }
}
