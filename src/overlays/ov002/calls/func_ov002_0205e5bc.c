/* Replace the owned UTF-16 string in the slot: free whatever is there, and when
 * the caller supplies a replacement allocate (length + 1) halfwords and copy it
 * in. A null replacement just clears the slot. */
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int func_020200c8(const void *text);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void func_020200e4(void *dst, const void *src);

void func_ov002_0205e5bc(void **slot, const void *text) {
    if (*slot != 0) {
        NNSi_FndFreeFromDefaultHeap(*slot);
        *slot = 0;
    }

    if (text == 0) {
        return;
    }

    {
        void *copy = NNSi_FndAllocFromDefaultExpHeap((func_020200c8(text) + 1) * 2);

        *slot = copy;
        func_020200e4(copy, text);
    }
}
