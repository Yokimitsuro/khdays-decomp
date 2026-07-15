/* NONMATCHING: correct; +4B register-allocation tie. The ROM keeps the base holder in r8 and
 * the GFXi 0-arg in r4 (5 callee-saved); our mwcc uses an extra register (sb) + a mov. Menu cell
 * DMA flush (7 slots). */
/* func_ov008_0204ffe4 -- flush the dirty menu cell buffers to VRAM, ov008.
 * For each of the 7 cell slots whose dirty bit is set in the object's mask byte (base+0x963c),
 * enqueues a GFX DMA from the slot's cell buffer (base+0x95a4 + slot*4) to the slot's VRAM
 * destination (data_ov008_0208e860[slot]) of length (base+0x95d0)<<6. Clears the mask after. */
extern void GFXi_EnqueueCommand(void *dst, int a, void *src, int size);
extern void *data_ov008_0208e860[];
extern int   data_ov008_02090f04[];

void func_ov008_0204ffe4(void) {
    unsigned int i = 0;
    do {
        char *o = (char *)data_ov008_02090f04[1] + 0x9000;
        if (*(unsigned char *)(o + 0x63c) & 1 << i) {
            GFXi_EnqueueCommand(data_ov008_0208e860[i], 0,
                                *(void **)(o + i * 4 + 0x5a4), *(int *)(o + 0x5d0) << 6);
        }
        i++;
    } while ((int)i < 7);
    *(unsigned char *)(data_ov008_02090f04[1] + 0x963c) = 0;
}
