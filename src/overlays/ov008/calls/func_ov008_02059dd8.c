extern void func_0202a7dc(void *object);
extern void func_0202a440(void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov008_02059dd8(void *object)
{
    if (*(signed char *)((char *)object + 1) != 0) {
        func_0202a7dc((char *)object + 4);

        if ((*(unsigned char *)object & 4) != 0) {
            func_0202a440((char *)object + 0x13c);
            NNSi_FndFreeFromDefaultHeap(*(void **)((char *)object + 0x160));
        }

        *(unsigned char *)object = 0;
    }
}
