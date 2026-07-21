typedef unsigned short u16;

extern void func_020262a0(u16 *dst, int count, const void *tmpl, unsigned int p6);
extern void func_02030278(int p1, int p2, int p3, int p4, int table, int p5);
extern int data_ov025_020b52c4;

void func_ov025_020a28b0(int p1, int p2, int p3, int p4, int p5, unsigned int p6) {
    u16 table[12];
    func_020262a0(table, 0xb, &data_ov025_020b52c4, p6);
    table[11] = 0;
    func_02030278(p1, p2, p3, p4, (int)table, p5);
}
