typedef unsigned short u16;

extern void func_020262a0(u16 *dst, int count, const void *tmpl, unsigned int p6);
extern void func_ov025_020a276c(int p1, int p2, int p3, int p4, int p5, int table);
extern int data_ov025_020b52cc;

void func_ov025_020a27e0(int p1, int p2, int p3, int p4, int p5, unsigned int p6) {
    u16 table[11];
    func_020262a0(table, 10, &data_ov025_020b52cc, p6);
    table[10] = 0;
    func_ov025_020a276c(p1, p2, p3, p4, p5, (int)table);
}
