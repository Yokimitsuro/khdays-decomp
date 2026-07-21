extern void func_ov062_020b7360(int obj, int arg);
/* Mark the actor as active (+0x11c = 1), clear its timer (+0x120) and tail-call the entry step. */
void func_ov062_020b7320(int unused, int obj) {
    *(int *)(obj + 0x11c) = 1;
    *(int *)(obj + 0x120) = 0;
    func_ov062_020b7360(obj, 0);
}
