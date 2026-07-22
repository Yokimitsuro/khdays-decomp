/* func_ov278_020d337c -- reaction step: while the gate byte at *node[9] is clear, notify the owner
 * with the constant pair at data_ov278_020d639c+8 (event 4), fire attack 0xe and hand off to
 * func_ov278_020d33f4.
 * The pair is copied member-wise HIGH HALFWORD FIRST and through a local pointer, which is what
 * puts `&pair` in a register before the copy and the two `ldrh` in the ROM's order. */
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov278_020d33f4(void);
extern char data_ov278_020d639c[];

struct Pair16 { unsigned short a, b; };

void func_ov278_020d337c(int self) {
    int *node = *(int **)(self + 4);
    struct Pair16 pair;
    struct Pair16 *ps;
    void (*cb)(int, void *, int);
    if (*(unsigned char *)node[9] != 0) {
        return;
    }
    ps = &pair;
    ps->b = ((struct Pair16 *)(data_ov278_020d639c + 8))->b;
    ps->a = ((struct Pair16 *)(data_ov278_020d639c + 8))->a;
    cb = *(void (**)(int, void *, int))(node[0] + 0x24);
    if (cb != 0) {
        cb(node[0], ps, 4);
    }
    func_ov107_020c9264(node[0], 0xe, 1);
    func_0203c634(self, *(signed char *)(self + 0x20), (int)&func_ov278_020d33f4);
}
