typedef unsigned short u16;
extern void func_020262a0(u16 *dst, int count, const void *tmpl, unsigned int a);
extern void func_ov008_02082d44(int p1, int table, int p3, int p4, int p5, int p6);
extern int data_ov008_02090ea0;

void func_ov008_02082d98(int p1, unsigned int p2, int p3, int p4, int p5) {
    u16 table[9];
    func_020262a0(table, 9, &data_ov008_02090ea0, p2);
    func_ov008_02082d44(p1, (int)table, p3, p4, p5, 0x20);
}
