/*
 * func_ov185_020ce344 -- x3 (ov185/186/187). Prime the group, then run each sub-node's +0x1f0
 * callback with the group arg. Call 020c887c(self); for i in 0..3, node = (*(self+0x390))[i], and
 * if node has a callback at +0x1f0, invoke cb(node, arg).
 */
extern void func_ov107_020c887c(int self);

void func_ov185_020ce344(int self, int arg) {
    int i;

    func_ov107_020c887c(self);
    for (i = 0; i < 4; i++) {
        int node = (*(int **)(self + 0x390))[i];
        void (*cb)(int, int) = *(void (**)(int, int))(node + 0x1f0);

        if (cb != 0) {
            cb(node, arg);
        }
    }
}
