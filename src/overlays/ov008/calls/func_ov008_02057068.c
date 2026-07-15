/* func_ov008_02057068 -- push the two menu counters into the event-flag store, ov008.
 * Writes the event context's counter fields (base+8 and base+0xc, base = *data_0204be18) into
 * flag groups 10 and 0x14 via func_ov008_02056fb8 (width 8, max 0xf423f, sub-ids 0x14/0x16). */
extern void func_ov008_02056fb8(int group, int value, int max, int width, int subId);
extern int  data_0204be18;

void func_ov008_02057068(void) {
    func_ov008_02056fb8(10, *(int *)(data_0204be18 + 8), 0xf423f, 8, 0x14);
    func_ov008_02056fb8(0x14, *(int *)(data_0204be18 + 0xc), 0xf423f, 8, 0x16);
}
