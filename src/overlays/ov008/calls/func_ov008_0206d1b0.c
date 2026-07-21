typedef unsigned short u16;
extern void func_020262a0(u16 *dst, int count, const void *tmpl, unsigned int a, unsigned int b);
extern void func_ov008_0206d0d8(int p1, int p2, int p3, int p4, int p5, int table);
extern int data_ov008_02090808;

void func_ov008_0206d1b0(int p1, int p2, int p3, int p4, int p5, unsigned int p6, unsigned int p7) {
    u16 table[21];
    func_020262a0(table, 0x14, &data_ov008_02090808, p6, p7);
    table[20] = 0;
    func_ov008_0206d0d8(p1, p2, p3, p4, p5, (int)table);
}
