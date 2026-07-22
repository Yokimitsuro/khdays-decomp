/* Duplicate a block onto the default heap and hand the copy back through the
 * out-parameter.
 *
 * The copy destination is read back THROUGH the out-parameter rather than from a
 * local holding the allocation. Both compile to the same register, but the
 * write-then-read-back form puts the store before the argument setup, which is
 * the order the ROM has. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);

void func_ov002_02057d04(void **out, const void *src, unsigned int size) {
    *out = NNSi_FndAllocFromDefaultExpHeap(size);
    MIi_CpuCopyFast(src, *out, size);
}
