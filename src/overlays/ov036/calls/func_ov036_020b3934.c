/* The argument address is built in two steps -- a hoisted `base = data + 0x2d94` and
 * `base + 0x14` at the call -- because the ROM splits it (add #0x194 / add #0x2c00 /
 * add #0x14) and the single `+ 0x2da8` form is 4 B short. */
extern void func_ov036_020b39b0(int p);
extern void func_ov036_020b3ac4(int self, int p, int c);
extern int data_ov036_020b4f40;

void func_ov036_020b3934(int self, int a, int b) {
    int base = *(int *)&data_ov036_020b4f40 + 0x2d94;
    if (*(int *)(self + 0x6bc) == 0x2f &&
        (*(int *)(self + 0x7b0) == 0 || *(int *)(self + 0x7b0) == 0xc000)) {
        func_ov036_020b39b0(base + 0x14);
    }
    func_ov036_020b3ac4(self, a + 0x14, b);
}
