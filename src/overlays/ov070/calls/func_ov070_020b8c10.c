extern void func_ov070_020b897c(int this, int slot, int p3);
extern int func_ov022_02095524(int x);
extern int func_ov022_02095554(int x);
extern void func_ov070_020b88e0(int p);

void func_ov070_020b8c10(int this, int base, int p3) {
    int i;
    int slot;
    slot = base + 0xc;
    i = 0;
    do {
        func_ov070_020b897c(this, slot, p3);
        i++;
        slot += 0x118;
    } while (i < 2);
    if (func_ov022_02095524(this + 0x22f8) == 0) return;
    if (*(int *)(base + 0x128) == 0) {
        func_ov070_020b88e0(base + 0x124);
    }
    if (func_ov022_02095554(this + 0x22f8) == 0) return;
    if (*(int *)(base + 0x10) != 0) return;
    func_ov070_020b88e0(base + 0xc);
}
