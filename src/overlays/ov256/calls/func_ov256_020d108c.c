extern void func_ov256_020d13e0(int target, int param_2);
/* Raise the "done" flag (+0x39c); when the actor is in state 1, forward to
 * the sub-target (+0x214) along with the second argument. */
void func_ov256_020d108c(int obj, int param_2) {
    *(int *)(obj + 0x39c) = 1;
    if (*(int *)(obj + 0x50) != 1) {
        return;
    }
    func_ov256_020d13e0(*(int *)(obj + 0x214), param_2);
}
