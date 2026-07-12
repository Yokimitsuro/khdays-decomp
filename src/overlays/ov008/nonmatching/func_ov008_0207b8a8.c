/* PROVEN TIE (register coloring only, same size/shape). The instruction stream is
 * byte-for-byte the ROM's except mwcc keeps &data in r0 and the countdown value in
 * r0, where the ROM keeps &data in r1 and the value in r2. Structure, splits
 * (base +0x400, offset +0xf2) and all relocs match. Kept here so the ov008 blob
 * stays byte-exact. */
extern int data_ov008_02090f24;
extern void WM_EndKeySharing_0x02023ad0(void);

void func_ov008_0207b8a8(void) {
    char *base;
    if (*(int *)((char *)&data_ov008_02090f24 + 4) == 0) return;
    base = (char *)(*(int *)&data_ov008_02090f24 + 0x400);
    if (*(unsigned short *)(base + 0xf2) != 0) {
        *(unsigned short *)(base + 0xf2) = *(unsigned short *)(base + 0xf2) - 1;
        return;
    }
    WM_EndKeySharing_0x02023ad0();
    *(int *)((char *)&data_ov008_02090f24 + 4) = 0;
}
