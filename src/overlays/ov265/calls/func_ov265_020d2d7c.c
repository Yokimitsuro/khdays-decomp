/* Allocate the 0x39c-byte sub-actor, back-link the owner at +0x388, install its update
 * handler at +0x18c, run the ov107 setup and return it. */
extern int func_0203d15c(int size);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov265_020d2db0(void);
int func_ov265_020d2d7c(int param_1) {
    int obj = func_0203d15c(0x39c);
    *(int *)(obj + 0x388) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov265_020d2db0;
    func_ov107_020c6624(obj, 0);
    return obj;
}
