/* PROVEN TIE (strength reduction / loop form). mwcc build 139 strength-reduces
 * param_1+i*8 into a walking pointer (advancing r5 by 8) and tests the loop
 * condition inline; the ROM keeps i in a register and recomputes the address with
 * `add r0,r5,r4,lsl#3` twice per iteration, rotating the loop with an initial
 * `b` to the test. Array-subscript forms only add a second induction variable.
 * Logically identical; kept here so the ov008 blob stays byte-exact. */
extern int func_ov008_0208b148(int arg);

int func_ov008_020830c8(int param_1) {
    int i;
    for (i = 0; i < 4; i++) {
        int p = *(int *)(param_1 + i * 8 + 0x14);
        if (p == 0) break;
        if (func_ov008_0208b148(*(int *)(p + 0x14)) < *(int *)(param_1 + i * 8 + 0x18)) {
            return 0;
        }
    }
    return 1;
}
