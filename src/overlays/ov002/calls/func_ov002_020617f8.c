/* Bind the widget's sub-node 3 to the descriptor at +0xe0, give it the caller's
 * depth (shifted into the fixed-point field) and refresh. */
extern void func_0202accc(void *self, int slot, void *desc, int a);
extern void func_01fff774(void *self, int slot, int value);
extern void func_0202af1c(void *self);

void func_ov002_020617f8(char *self, int depth) {
    func_0202accc(self, 3, self + 0xe0, 0);
    func_01fff774(self, 3, depth << 0xc);
    func_0202af1c(self);
}
