/* func_ov005_02058678 -- is the ov005 sub-context usable? True when the global is non-null and
 * its +8 handle is set; a null global counts as usable, which is what the ROM's preset `r1 = 1`
 * and the single `moveq r1,#0` inside the guard say. */
extern int data_ov005_0205b8d0;

int func_ov005_02058678(void) {
    int ok = 1;
    int p = *(int *)&data_ov005_0205b8d0;
    if (p != 0) {
        if (*(int *)(p + 8) == 0) {
            ok = 0;
        }
    }
    return ok != 0;
}
