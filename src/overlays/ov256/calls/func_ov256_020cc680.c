/* Scene hook of the ov256 enemy: adds its two +0x434 items and the five +0x43c items to the
 * scene (arg 1) and chains to the common handler. */
extern void func_ov107_020c2b20(int obj, int arg1);
extern void func_ov107_020c7b70(int obj, int arg1);

void func_ov256_020cc680(int *list, int target) {
    int i;
    for (i = 0; i < 2; i++)
        func_ov107_020c2b20(target, list[i + 0x10d]);
    for (i = 0; i < 0x5; i++)
        func_ov107_020c2b20(target, list[i + 0x10f]);
    func_ov107_020c7b70((int)list, target);
}
