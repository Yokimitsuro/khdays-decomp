/* NONMATCHING — single-register coloring tie (32/32, byte-identical except the base
 * pointer register: the ROM holds *global in r2, mwcc holds it in r1). The tail-call
 * target (ip), the param_1*4 index and the +0x220 load all match. Unsteerable with
 * param_1 pinned to r0; the raw blob keeps the build byte-exact.
 *
 * Forward the table entry at (*global)[param_1] + 0x220 to func_ov002_020593b4. */
extern int func_ov002_020593b4(int entry);
extern int data_ov002_0207f614;

int func_ov002_02056a78(int param_1) {
    return func_ov002_020593b4(*(int *)(*(int *)&data_ov002_0207f614 + param_1 * 4 + 0x220));
}
