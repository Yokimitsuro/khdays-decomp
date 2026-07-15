/* func_ov009_0205297c -- commit a menu action and mark it handled, ov009. Runs
 * func_ov009_02055d58(action) and sets the handled flag at obj+0x23c. */
extern void func_ov009_02055d58(int action);
void func_ov009_0205297c(char *obj, int action) {
    func_ov009_02055d58(action);
    *(int *)(obj + 0x23c) = 1;
}
