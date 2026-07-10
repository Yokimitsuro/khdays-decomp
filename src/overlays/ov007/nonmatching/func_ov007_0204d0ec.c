/* Equivalent, readable C. NOT byte-exact: size-exact (132) but the predicated
 * empty-line branch orders its two ops the other way (mwcc emits ldreq r2,=d170
 * then streq [+0x20]; the ROM stores first). A 2-instruction scheduling tie in
 * the predicated block — no mwcc generation matches (verify_sweep). Stub keeps
 * the blob byte-exact. */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov007_0204ce94(void *p);
extern int func_ov007_0204d170(void);
extern int func_ov007_0204cf7c(void);
extern unsigned short data_0204c190;
extern int func_ov007_0204d2d0(void);

/* After a 0xf-frame delay, pull the next text line (Ov007_CopyLine): if non-empty
 * bump the line counter and loop to cf7c, else advance to the next screen (d170).
 * The B-button (input bit 8) skips straight to the fade-out (d2d0). */
int func_ov007_0204d0ec(void) {
    int root = NNSi_FndGetCurrentRootHeap();
    int ret = 0;
    int frame = *(int *)(root + 0x20) + 1;

    *(int *)(root + 0x20) = frame;
    if (frame >= 0xf) {
        func_ov007_0204ce94((void *)root);
        if (*(unsigned short *)(root + 0x7c) != 0) {
            *(int *)(root + 0x70) = *(int *)(root + 0x70) + 1;
            ret = (int)func_ov007_0204cf7c;
            *(int *)(root + 0x20) = 0;
        } else {
            *(int *)(root + 0x20) = 0;
            ret = (int)func_ov007_0204d170;
        }
    }
    if ((data_0204c190 & 8) != 0) {
        *(int *)(root + 0x20) = 0;
        ret = (int)func_ov007_0204d2d0;
    }
    return ret;
}
