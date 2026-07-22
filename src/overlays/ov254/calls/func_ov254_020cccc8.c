/* func_ov254_020cccc8 -- rebind the two sub-objects (+0x384 and +0x388) to fresh resources for
 * this slot. The first takes kind `slot + 1` and the transform block at +0x38c, the second kind
 * `slot + 0x20` and the block at +0x3b0. */
extern int func_ov107_020c9440(int obj, int kind);
extern void func_ov254_020ccc50(int a, int b, int c, int d);

void func_ov254_020cccc8(int obj, int slot, int arg) {
    func_ov254_020ccc50(*(int *)(obj + 0x384), obj + 0x38c,
                        func_ov107_020c9440(obj, slot + 1), arg);
    func_ov254_020ccc50(*(int *)(obj + 0x388), obj + 0x3b0,
                        func_ov107_020c9440(obj, slot + 0x20), arg);
}
