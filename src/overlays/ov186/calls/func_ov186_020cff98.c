/*
 * func_ov186_020cff98 -- x3 (ov185/186/187). Notify each of the 4 sub-nodes, run its callback,
 * then clear a flag word; finish by ticking the owner. For i in 0..3, node = (*(self+0x390))[i]:
 * ping the owner via 020c2b20(arg, node); if node has a callback at +0x1f0, call cb(node,
 * *(u8)(self+0x19e)); then zero node+0x220. Hand off with 020c7b70(self, arg).
 */
extern void func_ov107_020c2b20(int owner, int node);
extern void func_ov107_020c7b70(int self, int arg);

void func_ov186_020cff98(int self, int arg) {
    int i;

    for (i = 0; i < 4; i++) {
        int node = (*(int **)(self + 0x390))[i];
        void (*cb)(int, unsigned char);
        unsigned char b;

        func_ov107_020c2b20(arg, node);
        node = (*(int **)(self + 0x390))[i];
        b = ((unsigned char *)self)[0x19e];
        cb = *(void (**)(int, unsigned char))(node + 0x1f0);
        if (cb != 0) {
            cb(node, b);
        }
        node = (*(int **)(self + 0x390))[i];
        *(int *)(node + 0x220) = 0;
    }
    func_ov107_020c7b70(self, arg);
}
