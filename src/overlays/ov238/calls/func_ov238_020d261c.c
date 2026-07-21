extern void func_ov238_020d29c8(int target);
/* Raise the "done" flag (+0x390); when the actor is in state 1, notify its sub-target (+0x214). */
void func_ov238_020d261c(int obj) {
    *(int *)(obj + 0x390) = 1;
    if (*(int *)(obj + 0x50) != 1) {
        return;
    }
    func_ov238_020d29c8(*(int *)(obj + 0x214));
}
