/* func_ov008_02080820 -- flush the dirty title cell buffers to VRAM, ov006.
 * For each of the 8 cell slots whose dirty bit is set in the object's mask byte (obj+0x9570),
 * enqueues a 0x600-byte GFX DMA from the slot's cell buffer (obj+0x94cc + slot*4) to the
 * slot's VRAM destination (data_ov008_0208fd6c[slot]). Clears the whole dirty mask afterward. */
extern void GFXi_EnqueueCommand(void *dst, int a, void *src, int size);
extern void *data_ov008_0208fd6c[];
extern int *data_ov008_02090fa4;

void func_ov008_02080820(void) {
    unsigned int i = 0;
    do {
        if (*(unsigned char *)((char *)data_ov008_02090fa4 + 0x9570) & 1 << i) {
            GFXi_EnqueueCommand(data_ov008_0208fd6c[i], 0,
                                ((void **)((char *)data_ov008_02090fa4 + 0x94cc))[i], 0x600);
        }
        i++;
    } while ((int)i < 8);
    *(unsigned char *)((char *)data_ov008_02090fa4 + 0x9570) = 0;
}
