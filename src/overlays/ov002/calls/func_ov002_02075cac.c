/* Upload one 0x80-byte tile row to BG3 char VRAM at 0x10c0, picking the row from
 * the far end of the table: index 3 - <current slot>. func_ov105_020bd7c4 is
 * called twice and the first result discarded -- that is the ROM, not a
 * transcription slip. */
extern int func_ov105_020bd7c4(void);
extern void GX_LoadBG3Char(void *src, unsigned int offset, unsigned int size);

extern int data_ov002_0207fa18;

void func_ov002_02075cac(void) {
    int offset;

    func_ov105_020bd7c4();
    offset = (3 - func_ov105_020bd7c4()) * 0x80 + 0x20;
    GX_LoadBG3Char((void *)(*(int *)(data_ov002_0207fa18 + 0x10) + offset), 0x10c0, 0x80);
}
