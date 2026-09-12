/* func_ov146_020cc2f4 -- hand both sub-objects (+0x3b8, +0x3bc) to the visitor and then run the
 * base pass. The visitor takes (arg, object), not the other way round. */
extern void func_ov107_020c2b20(int arg, int obj);
extern void func_ov107_020c7b70(int obj, int arg);

void func_ov146_020cc2f4(int obj, int arg) {
    func_ov107_020c2b20(arg, *(int *)(obj + 0x3b8));
    func_ov107_020c2b20(arg, *(int *)(obj + 0x3bc));
    func_ov107_020c7b70(obj, arg);
}
