/* Create channel `index`: allocate the caller-sized block into the slot array at
 * +0x18, stamp the index at +0, clear the state byte at +2, write the kind at
 * +0x112 and the owner at +0x111, and mark the key at +0x114 unset. Reports the
 * block, re-read from the slot rather than reused from the allocation. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);

void *func_ov022_0208b71c(char *self, int index, int kind, int owner,
                          unsigned int size) {
    char *slots = self + 0x18;

    *(void **)(slots + index * 4) = NNSi_FndAllocFromDefaultExpHeap(size);

    {
        char *block = *(char **)(slots + index * 4);

        block[0] = (char)index;
        block[2] = 0;
        block[0x112] = (char)kind;
        block[0x111] = (char)owner;
        *(unsigned short *)(block + 0x114) = 0xffff;
    }

    return *(void **)(slots + index * 4);
}
