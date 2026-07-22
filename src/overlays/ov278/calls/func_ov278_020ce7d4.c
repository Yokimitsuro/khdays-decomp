/* func_ov278_020ce7d4 -- twin of func_ov278_020cd8cc, reading the pose block from the parent at
 * +0x384 instead of +0x394. Same array-index-with-folded-offset form. */
extern void func_ov107_020c5c14(int obj, int mode);
extern void func_ov107_020c7b70(int obj, int arg);

void func_ov278_020ce7d4(int obj, int arg) {
    int i;
    for (i = 0; i < 4; i++) {
        ((int *)obj)[i + 0x6d] = ((int *)*(int *)(obj + 0x384))[i + 0x6d];
    }
    func_ov107_020c5c14(obj, 2);
    func_ov107_020c7b70(obj, arg);
}
