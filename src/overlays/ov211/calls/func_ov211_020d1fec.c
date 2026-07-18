/*
 * func_ov211_020d1fec -- x3. Message handler: map the kind through a 26-entry table, then set up a
 * sub-object. A local copy of the const table (data_020d4684) is indexed by kind; the result feeds
 * 020c9440(self, table[kind]). Hand that plus bit0 of self[0x311] to the 020d0388 sub-object setup
 * (self, self[0x384], handle, flag, self+0x388), then reset via 0203c7ac.
 */
struct t26 { int w[26]; };
struct b1 { unsigned char b0 : 1; };
extern int  func_ov107_020c9440(int self, int x);
extern void func_ov211_020d21a8(int a1, int a2, int a3, int a4, int a5);
extern void func_0203c7ac(int a, int b);
extern struct t26 data_ov211_020d64a4;

void func_ov211_020d1fec(int self, int kind) {
    struct t26 table = data_ov211_020d64a4;

    func_ov211_020d21a8(self, *(int *)(self + 0x384), func_ov107_020c9440(self, table.w[kind]),
                        ((struct b1 *)(self + 0x311))->b0, self + 0x388);
    func_0203c7ac(*(int *)(self + 0x384), 0);
}
