/* Allocate the 0x3a4-byte sub-actor, back-link the owner at +0x38c, install its update
 * handler at +0x18c, run the ov107 setup and return it. */
extern int func_0203d15c(int size);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov229_020d5cb8(void);
int func_ov229_020d5c84(int param_1) {
    int obj = func_0203d15c(0x3a4);
    *(int *)(obj + 0x38c) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov229_020d5cb8;
    func_ov107_020c6624(obj, 0);
    return obj;
}
