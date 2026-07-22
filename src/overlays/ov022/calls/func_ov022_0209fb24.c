/* Arm the decoder: raise bit 0 of the 64-bit state word at the root heap, install
 * the frame callback at +0x460, and hand back the entry point.
 *
 * The state word is 64-BIT -- that is why the high half is OR-ed with zero and
 * stored back, which reads as a no-op until you notice the pair. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_020a37d0(void);
extern void func_ov022_02095940(void);

void *func_ov022_0209fb24(void) {
    char *heap = (char *)NNSi_FndGetCurrentRootHeap();

    *(unsigned long long *)heap |= 1;
    *(void **)(heap + 0x460) = (void *)func_ov022_020a37d0;

    return (void *)func_ov022_02095940;
}
