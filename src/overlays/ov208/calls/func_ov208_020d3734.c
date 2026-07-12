/* Allocate a 0x410-byte object, link it back to this owner (+0x394), install the ov208_020d3768
 * callback (+0x18c), initialise it via ov107_020c6624 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov208_020d3768(int);
int func_ov208_020d3734(int param_1) {
    int obj = func_0203d15c(0x410);
    *(int *)(obj + 0x394) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov208_020d3768;
    func_ov107_020c6624(obj, 0);
    return obj;
}
