/*
 * func_ov277_020cd130 -- x3 (ov185/186/187). Prime the group, then run each sub-node's +0x1ec
 * callback with the group arg. Call 020c887c(self); for i in 0..3, node = (*(self+0x400))[i], and
 * if node has a callback at +0x1ec, invoke cb(node, arg).
 */
extern void func_ov107_020c8500(int self);

void func_ov277_020cd130(int self, int arg) {
    int i;

    func_ov107_020c8500(self);
    for (i = 0; i < 2; i++) {
        int node = (*(int **)(self + 0x400))[i];
        void (*cb)(int, int) = *(void (**)(int, int))(node + 0x1ec);

        if (cb != 0) {
            cb(node, arg);
        }
    }
}
