/* func_ov008_0205ea88 -- switch the panel to page param_2 (negative = none).
 * Points obj+0x300 at that page's list (obj+0x304 + page*0xc) and obj+0x78 at its header
 * (obj+page*4+0x7c); then refreshes every node's cached counter byte (+5) from the per-row
 * counters at obj+0x1bf0.
 *
 * PROVENANCE: byte-identical twin of func_ov025_02090ffc -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern int *NNS_FndGetNextListObject(void *list, int obj);

void func_ov008_0205ea88(int param_1, int param_2) {
    int header;
    if (param_2 < 0) {
        header = 0;
        *(int *)(param_1 + 0x300) = 0;
    } else {
        *(int *)(param_1 + 0x300) = param_2 * 0xc + (param_1 + 0x304);
        header = *(int *)(param_1 + param_2 * 4 + 0x7c);
    }
    *(int *)(param_1 + 0x78) = header;
    {
        int *n = NNS_FndGetNextListObject(*(void **)(param_1 + 0x300), 0);
        if (n != 0) {
            do {
                *(unsigned char *)((int)n + 5) =
                    *(unsigned char *)(param_1 + *(int *)(*n + 0x14) + 0x1bf0);
                n = NNS_FndGetNextListObject(*(void **)(param_1 + 0x300), (int)n);
            } while (n != 0);
        }
    }
}
