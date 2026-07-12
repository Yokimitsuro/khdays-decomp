/* Allocate a 0x1c-byte object, initialise it via 020cb5c8 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020cb5c8(int a);
int func_ov107_020cb5ac(void) {
    int obj = func_0203d15c(0x1c);
    func_ov107_020cb5c8(obj);
    return obj;
}
