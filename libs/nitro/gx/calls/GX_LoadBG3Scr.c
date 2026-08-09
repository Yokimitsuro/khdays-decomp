/* NitroSDK GX_LoadBG3Scr -- load BG3 screen data for the main engine.
 *
 * DMA when a channel is configured (data_020422b8 != -1) and the transfer beats the 0x1c-byte
 * threshold; otherwise a CPU copy. One of 8 byte-identical siblings (BG0..BG3 x main/sub) that
 * differ only in which G2/G2S pointer getter they call.
 *
 * The C symbol keeps the index's name for delinking, but THAT NAME IS WRONG: the SDK identifier
 * shape-matched all 8 to "GX_LoadBG0Scr". The getter is what identifies it -- G2_* is the main engine,
 * G2S_* the sub engine, and the BGn in the getter is the real BG number. Ghidra carries the
 * correct name (GX_LoadBG3Scr). */
extern void *G2_GetBG3ScrPtr(void);
extern void MI_DmaCopy16(int dmaNo, const void *src, void *dst, unsigned int size);
extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int size);
extern int data_020422b8;

void GX_LoadBG3Scr(const void *src, unsigned int offset, unsigned int size) {
    unsigned char *base = (unsigned char *)G2_GetBG3ScrPtr();

    if (data_020422b8 != -1 && size > 0x1c) {
        MI_DmaCopy16(data_020422b8, src, base + offset, size);
    } else {
        MIi_CpuCopy16(src, base + offset, size);
    }
}
