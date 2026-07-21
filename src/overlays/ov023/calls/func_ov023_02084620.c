extern int func_02021980(int vm, unsigned short *pc);
extern unsigned int func_02020d10(int vm, int idx);
extern void func_0202bef4(unsigned int a, int b, int c);
/* Script op: read an int operand, resolve it as a wrapped index, dispatch it (u16); return 1. */
int func_ov023_02084620(int vm, unsigned short *pc) {
    int idx = func_02021980(vm, pc);
    unsigned int resolved = func_02020d10(vm, idx);
    func_0202bef4(resolved & 0xffff, 0, 0);
    return 1;
}
