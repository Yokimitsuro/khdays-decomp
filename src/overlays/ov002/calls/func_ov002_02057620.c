/* Cancel the slot named by the index: nothing to do while
 * func_ov002_02059520 reports it busy, otherwise release it as kind 3 and mark
 * the byte at +0x65 of the slot record 0xf. The context global is re-read for
 * that last store rather than cached -- that is the ROM. */
extern int func_ov002_02059520(int slot);
extern void func_ov002_02057260(int slot, int kind);

extern char *data_ov002_0207f614;

void func_ov002_02057620(int index) {
    int slot = *(int *)(data_ov002_0207f614 + index * 4 + 0x220);

    if (func_ov002_02059520(slot) != 0) {
        return;
    }

    func_ov002_02057260(slot, 3);
    *(unsigned char *)(data_ov002_0207f614 + slot + 0x65) = 0xf;
}
