/* Allocate a 0x120-byte object, initialise it via 020c0dd0 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c0dd0(int a);
int func_ov107_020c0db4(void) {
    int obj = func_0203d15c(0x120);
    func_ov107_020c0dd0(obj);
    return obj;
}
