/*
 * func_ov186_020d01a4 -- x3 (ov185/186/187). Run each sub-node's +0x1f8 callback, then close.
 * For i in 0..3, node = (*(self+0x390))[i]; cb = *(node + 0x1f8); if set, call cb(node). Finish
 * with 020c88fc(self).
 */
extern void func_ov107_020c88fc(int self);

void func_ov186_020d01a4(int self) {
    int i;

    for (i = 0; i < 4; i++) {
        int node = (*(int **)(self + 0x390))[i];
        void (*cb)(int) = *(void (**)(int))(node + 0x1f8);

        if (cb != 0) {
            cb(node);
        }
    }
    func_ov107_020c88fc(self);
}
