/* Flush the dirty menu cell buffers to VRAM. For each of the 7 cell slots whose bit is set
 * in the mask byte at +0x963c, enqueue a GFX DMA from the slot's cell buffer (+0x95a4 + slot*4)
 * to the slot's VRAM destination, with a length of (+0x95d0) << 6; then clear the whole mask.
 *
 * Same shape as func_ov000_02052fdc, which flushes the title logo's three sub-layers. Taking
 * that sibling's form is what made it match: the object pointer has to be re-read from the
 * global INSIDE the loop, the counter has to be a plain signed int in a `for`, and the mask
 * test has to be written `1 << i`. The park note here blamed register allocation and an extra
 * callee-saved register; that was a symptom of the do/while-with-unsigned-counter shape, not
 * a compiler tie. */
extern void GFXi_EnqueueCommand(int dest, int a, int src, int size);
extern int  data_ov025_020b37c4[];
extern int  data_ov025_020b5744[];

void func_ov025_02083e0c(void) {
    int i;
    for (i = 0; i < 7; i++) {
        char *base = (char *)data_ov025_020b5744[1];
        if (*(unsigned char *)(base + 0x963c) & (1 << i)) {
            GFXi_EnqueueCommand(data_ov025_020b37c4[i], 0,
                                ((int *)(base + 0x95a4))[i],
                                *(int *)(base + 0x95d0) << 6);
        }
    }
    *(unsigned char *)((char *)data_ov025_020b5744[1] + 0x963c) = 0;
}
