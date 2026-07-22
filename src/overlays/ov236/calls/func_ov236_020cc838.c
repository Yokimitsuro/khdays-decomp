/* func_ov236_020cc838 -- hand both sub-objects (+0x3b4, +0x3b8) to the visitor and then run the
 * base pass. The visitor takes (arg, object), not the other way round. */
extern void func_ov107_020c2b38(int arg, int obj);
extern void func_ov107_020c7c1c(int obj, int arg);

void func_ov236_020cc838(int obj, int arg) {
    func_ov107_020c2b38(arg, *(int *)(obj + 0x3b4));
    func_ov107_020c2b38(arg, *(int *)(obj + 0x3b8));
    func_ov107_020c7c1c(obj, arg);
}
