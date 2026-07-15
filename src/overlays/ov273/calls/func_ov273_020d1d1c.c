/* c634 handler: set obj->f48 = self->f0->f2c*30/10, query func_ov107_020cab14; if it
 * returns 0, latch owner->+0x1c7 = 2 and dispatch with null cb. Otherwise bail if
 * *(obj->f8) is set; else reset obj->f1c, set obj->f48 = self->f0->f2c*30/2, notify
 * func_ov107_020c9264(owner, 2, 1), and dispatch via func_0203c634. */
extern int func_ov107_020cab14(int owner, int a);
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov273_020d1de4(void);
void func_ov273_020d1d1c(int self) {
    int obj = *(int *)(self + 4);
    *(int *)(obj + 0x48) = *(int *)(*(int *)self + 0x2c) * 30 / 10;
    *(int *)(obj + 0x24) = func_ov107_020cab14(*(int *)obj, 0);
    if (*(int *)(obj + 0x24) == 0) {
        *(unsigned char *)(*(int *)obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (*(unsigned char *)(*(int *)(obj + 8)) != 0) {
        return;
    }
    *(int *)(obj + 0x1c) = 0;
    *(int *)(obj + 0x48) = *(int *)(*(int *)self + 0x2c) * 30 / 2;
    func_ov107_020c9264(*(int *)obj, 2, 1);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov273_020d1de4);
}
