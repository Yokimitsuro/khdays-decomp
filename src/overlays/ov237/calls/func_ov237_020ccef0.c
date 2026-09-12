/* Forward the sub-object at (obj)+0x3e0, and (if present) the one at +0x4a4, to the ov107
 * callback dispatcher, then run the base ov107 attach for the pair. */
extern void func_ov107_020c2b20(int obj, int arg1);
extern void func_ov107_020c7b70(int obj, int arg1);

void func_ov237_020ccef0(int param_1, int param_2) {
    func_ov107_020c2b20(param_2, *(int *)(param_1 + 0x3e0));

    int field_4a4 = *(int *)(param_1 + 0x4a4);
    if (field_4a4 != 0) {
        func_ov107_020c2b20(param_2, field_4a4);
    }

    func_ov107_020c7b70(param_1, param_2);
}
