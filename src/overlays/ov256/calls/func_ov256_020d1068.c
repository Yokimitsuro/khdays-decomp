extern void func_ov256_020d13d0(int target);
/* Raise the "done" flag (+0x3a0); when the actor is in state 1, notify its sub-target (+0x214). */
void func_ov256_020d1068(int obj) {
    *(int *)(obj + 0x3a0) = 1;
    if (*(int *)(obj + 0x50) != 1) {
        return;
    }
    func_ov256_020d13d0(*(int *)(obj + 0x214));
}
