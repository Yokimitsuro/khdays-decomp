/* ⚠ func_0203c7ac takes TWO arguments here, not four. Ghidra shows a 4-arg call because
 * r2/r3 still hold leftovers at that point -- but the preceding `bl` clobbered them, so
 * they are garbage, not arguments. Passing p4 makes mwcc save it in a callee-saved
 * register (+16 B). */
struct Flags40 { int b0 : 1, b1 : 1; };
extern void func_ov107_020c5c54();
extern void func_0203c7ac(int a, int b);
extern void func_ov237_020d0cac(int a, void *b);

void func_ov237_020d0a4c(int self, int p2, void *p3, int p4) {
    void (*cb)(int, int);

    func_ov107_020c5c54(self, p2, p3, p4);
    if (((struct Flags40 *)(self + 0x40))->b1) {
        cb = *(void (**)(int, int))(self + 0xc);
        if (cb != 0) {
            cb(self, 0);
        }
    }
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x38c) = 1;
    if (*(int *)(self + 0x50) == 1) {
        func_ov237_020d0cac(*(int *)(self + 0x214), p3);
    }
}
