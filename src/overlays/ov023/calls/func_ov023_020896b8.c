/* func_ov023_020896b8 -- ov023 sub-scene entry: latch the root heap into data_ov023_0208a7c0,
 * clear +0x70, and prime both 4-byte slots at +0x60 (handle 0) and +0x68 (0x1f). Hands back the
 * per-frame state function.
 *
 * The loop counter, the offset and the value stored at +0x60 are all THE SAME ZERO in the ROM
 * (`movs r1,#0` then two `adds rN,r1,#0` copies), so they are written here as one `i = 0` that
 * the other two are seeded from. Three independent `= 0` initialisers mis-colour the block. */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov023_020896fc(void);
extern void func_ov023_02089848(void);
extern int data_ov023_0208a7c0;

void *func_ov023_020896b8(void) {
    int i;
    int off;
    int zero;
    *(int *)&data_ov023_0208a7c0 = NNSi_FndGetCurrentRootHeap();
    i = 0;
    *(int *)(*(int *)&data_ov023_0208a7c0 + 0x70) = i;
    off = i;
    zero = i;
    for (; i < 2; i++) {
        *(int *)(*(int *)&data_ov023_0208a7c0 + off + 0x60) = zero;
        *(int *)(*(int *)&data_ov023_0208a7c0 + off + 0x68) = 0x1f;
        off += 4;
    }
    func_ov023_020896fc();
    return (void *)func_ov023_02089848;
}
