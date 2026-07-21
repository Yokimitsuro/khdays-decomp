typedef unsigned short u16;
extern void func_020262a0(u16 *dst, int count, const void *tmpl, unsigned int a);
extern void func_ov026_02085bf4(int p1, int table, int p3, int p4, int p5, int p6);
extern int data_ov026_0209130c;

void func_ov026_02085c48(int p1, unsigned int p2, int p3, int p4, int p5) {
    u16 table[9];
    func_020262a0(table, 9, &data_ov026_0209130c, p2);
    func_ov026_02085bf4(p1, (int)table, p3, p4, p5, 0x20);
}
