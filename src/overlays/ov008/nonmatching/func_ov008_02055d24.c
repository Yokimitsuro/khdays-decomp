/* NONMATCHING: structurally byte-exact (116B) except one register-allocation swap -- the ROM
 * holds n-1 in ip and the loop counter in r3; our mwcc swaps them (r3/ip). Only register numbers
 * differ across ~5 instructions. Active hit-entry -> cursor record copy. */
/* func_ov008_02055d24 -- copy the active touch/hit entry into the menu's cursor record, ov008.
 * Snapshots the up-to-5-entry hit table (func_02024da4, 4 shorts each) into a stack buffer,
 * scans it backwards for the newest entry whose flag word (entry.w[3]) is 0, and copies that
 * 8-byte entry into the shared cursor record (*data_ov008_02090f14). If none qualify, copies
 * the oldest entry. */
struct HitEntry { unsigned short w[4]; };
extern int  func_02024da4(int buf);
extern void MI_CpuCopy8(unsigned short *src, unsigned short *dst, int size);
extern int  data_ov008_02090f14;

void func_ov008_02055d24(void) {
    struct HitEntry buf[5];
    int n1 = func_02024da4((int)buf) - 1;
    int i;
    for (i = n1; i >= 0; i--) {
        if (buf[i].w[3] == 0) {
            MI_CpuCopy8((unsigned short *)&buf[i], (unsigned short *)data_ov008_02090f14, 8);
            return;
        }
    }
    MI_CpuCopy8((unsigned short *)&buf[n1], (unsigned short *)data_ov008_02090f14, 8);
}
