struct bit1 { unsigned char b : 1; };

extern void func_ov070_020b8b40(int this, int slot, int i);

void func_ov070_020b8c9c(int this, int base) {
    int i;
    int slot;
    if (!((struct bit1 *)(this + 0x694))->b) return;
    slot = base + 0xc;
    i = 0;
    do {
        func_ov070_020b8b40(this, slot, i);
        i++;
        slot += 0x118;
    } while (i < 2);
}
