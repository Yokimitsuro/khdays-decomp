/* NitroSDK GXS_LoadBG0Char -- load BG0 character data for the sub engine.
 *
 * DMA when a channel is configured (data_020422b8 != -1) and the transfer beats the 0x30-byte
 * threshold; otherwise a CPU copy. One of 8 byte-identical siblings (BG0..BG3 x main/sub) that
 * differ only in which G2/G2S pointer getter they call.
 *
 * The C symbol keeps the index's name for delinking, but THAT NAME IS WRONG: the SDK identifier
 * shape-matched all 8 to "GX_LoadBG0Char". The getter is what identifies it -- G2_* is the main engine,
 * G2S_* the sub engine, and the BGn in the getter is the real BG number. Ghidra carries the
 * correct name (GXS_LoadBG0Char). */
extern void *G2S_GetBG0CharPtr(void);
extern void MI_DmaCopy32(int dmaNo, const void *src, void *dst, unsigned int size);
extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int size);
extern int data_020422b8;

void GXS_LoadBG0Char(const void *src, unsigned int offset, unsigned int size) {
    unsigned char *base = (unsigned char *)G2S_GetBG0CharPtr();

    if (data_020422b8 != -1 && size > 0x30) {
        MI_DmaCopy32(data_020422b8, src, base + offset, size);
    } else {
        MIi_CpuCopy32(src, base + offset, size);
    }
}
