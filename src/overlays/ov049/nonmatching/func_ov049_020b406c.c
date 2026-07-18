/* NONMATCHING -- 88/88 B, 7 differing bytes. SAME SHAPE and same 7-byte residue as
 * src/overlays/ov047/nonmatching/func_ov047_020b3b40.c -- read that note for the full
 * analysis (the `char *` base, the 60-permutation declaration sweep, the ruled-out forms).
 * They are separate families only because the pool literal differs (0x2e20 vs 0x2d78).
 *
 * Additionally ruled out here, measured with bytedist.py: computing `row + off` into an int
 * before the call (7, no change), folding +0x130 into it (14, worse), splitting it into two
 * locals (7, no change), and `do {...} while (1)` with an explicit break (7, no change).
 * Whatever fixes one of these two fixes both. */
extern void WM_EndKeySharing_0x020b15a4(int a, int b);
extern int data_ov049_020b4d00;

void func_ov049_020b406c(int self) {
    int i = 0;
    int p = *(int *)&data_ov049_020b4d00 + 0x2e20;
    char *base = (char *)self + 0x2000;
    int obj = *(int *)(base + 0x644);
    int off = 0;

    do {
        int row = *(int *)(obj + 0xc);
        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x63c), p);
        i = i + 1;
        *(int *)(row + off + 0x130) = p;
        off = off + 0x1c8;
        p = p + 0x24;
    } while (i < 10);
}
