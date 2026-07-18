/*
 * func_ov210_020d3f98 -- x3 (ov210/...). Rebuild the sub-object, then notify with a 1-bit flag.
 * Store func_020d402c(self, node, c, d) into self[0x194]. If self has a notify callback at +0x14,
 * call cb(self, bit1_signed) where bit1_signed = (*(node+0x40) << 30) >> 31 (0 or -1 from bit 1).
 */
extern int func_ov210_020d402c(int self, int node, int c, int d);

void func_ov210_020d3f98(int self, int node, int c, int d) {
    void (*cb)(int, int);
    int flag;

    *(int *)(self + 0x194) = func_ov210_020d402c(self, node, c, d);
    flag = (*(int *)(node + 0x40) << 30) >> 31;
    cb = *(void (**)(int, int))(self + 0x14);
    if (cb != 0) {
        cb(self, flag);
    }
}
