/* Two different treatments in one function, and both are needed:
 *  - the loaded field goes into `arg0`, OVERWRITING the unused parameter. A fresh local
 *    there makes mwcc put it in r3 and shifts everything.
 *  - the sum goes into a FRESH local, not into `arg2`. Writing `arg2 = arg0 + arg2`
 *    makes mwcc canonicalise to `add r2,r2,r0` (destination-first); the ROM has
 *    `add r2,r0,r2`, which is what a new value inheriting r2 looks like.
 * So it is not "always reuse the parameter" -- decide per value, from which register
 * the ROM gives it. */
int func_ov022_020915bc(int arg0, int arg1, int arg2) {
    int *pp;
    int sum;
    arg0 = *(int *)(arg1 + 4);
    pp = *(int **)(arg1 + 0x138);
    sum = arg0 + arg2;
    *(int *)(arg1 + 4) = sum;
    if (sum >= pp[7] && *(char *)(arg1 + 2) == 1) {
        *(int *)(arg1 + 4) = 0;
        *(char *)(arg1 + 2) = 2;
    }
    return 0;
}
