/* Recompute the visible-column mask at +0x4b0 and refresh only when it actually
 * changed. The mask is (1 << columns) - 1 taken from the count at +0x4ae, or
 * zero when the caller passes nothing or func_ov002_020575d0 reports the panel
 * suppressed. */
extern int func_ov002_020575d0(void);
extern void func_ov002_0205e018(void);

extern char *data_ov002_0207f620;

void func_ov002_0205e178(int enable) {
    char *ctx = data_ov002_0207f620;
    int mask;

    if (func_ov002_020575d0() != 0) {
        enable = 0;
    }

    if (enable != 0) {
        mask = (1 << *(unsigned short *)(ctx + 0x4ae)) - 1;
    } else {
        mask = 0;
    }

    if (*(int *)(ctx + 0x4b0) != mask) {
        *(int *)(ctx + 0x4b0) = mask;
        func_ov002_0205e018();
    }
}
