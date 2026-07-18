/*
 * func_ov255_020cc94c -- x3 (ov185/186/187). Ping all 9 sub-nodes, then tick the owner.
 * For i in 0..3, call 020c2b38(arg, (*(self+0x3f0))[i]); finish with 020c7c1c(self, arg).
 */
extern void func_ov107_020c2b20(int owner, int node);
extern void func_ov107_020c7b70(int self, int arg);

void func_ov255_020cc94c(int self, int arg) {
    int i;

    for (i = 0; i < 9; i++) {
        func_ov107_020c2b20(arg, (*(int **)(self + 0x3f0))[i]);
    }
    func_ov107_020c7b70(self, arg);
}
