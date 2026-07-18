/*
 * func_ov208_020d0694 -- x3. Message handler: map the message kind through a 15-entry table and
 * forward. A local copy of the const table (data_020d4798) is indexed by kind; the result feeds
 * 020c9440(self, table[kind]), whose handle goes to 020d0628(*(self+0x384), handle, arg3, self+0x388).
 * Finish with a reset (0203c7ac).
 */
struct t15 { int w[15]; };
extern int  func_ov107_020c9440(int self, int x);
extern void func_ov208_020d0628(int a, int b, int c, int d);
extern void func_0203c7ac(int a, int b);
extern struct t15 data_ov208_020d4798;

void func_ov208_020d0694(int self, int kind, int arg3) {
    struct t15 table = data_ov208_020d4798;

    func_ov208_020d0628(*(int *)(self + 0x384), func_ov107_020c9440(self, table.w[kind]), arg3,
                        self + 0x388);
    func_0203c7ac(*(int *)(self + 0x384), 0);
}
