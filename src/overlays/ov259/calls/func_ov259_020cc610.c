/* func_ov259_020cc610 -- hand both sub-objects (+0x384, +0x388) to the visitor and then run the
 * base pass. The visitor takes (arg, object), not the other way round. */
extern void func_ov107_020c2b20(int arg, int obj);
extern void func_ov107_020c7b70(int obj, int arg);

void func_ov259_020cc610(int obj, int arg) {
    func_ov107_020c2b20(arg, *(int *)(obj + 0x384));
    func_ov107_020c2b20(arg, *(int *)(obj + 0x388));
    func_ov107_020c7b70(obj, arg);
}
