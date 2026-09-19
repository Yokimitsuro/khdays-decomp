/* Wander entry: sets obj->+0x48 = self->f0->f2c*30/10 and, unless *(obj->+8) is set, plays
 * pose 2 (looping), picks a random turn direction (+0x18 = -1 or +1), clears the +0x1c timer
 * and dispatches to 020cdb1c. */
extern void func_ov107_020c9264(int owner, int a, int b);
extern int func_02023eb4();  /* K&R decl: needed for the rand `+ (v - v)` copy artifact */
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov273_020d175c(void);
void func_ov273_020d16d0(int self) {
    int obj = *(int *)(self + 4);
    int v;
    *(int *)(obj + 0x48) = *(int *)(*(int *)self + 0x2c) * 30 / 10;
    if (*(unsigned char *)(*(int *)(obj + 8)) != 0) {
        return;
    }
    func_ov107_020c9264(*(int *)obj, 2, 1);
    /* +(v-v) forces `adds r0,r0,#0` (rand result copied+tested); +0 would fold away */
    *(int *)(obj + 0x18) = (func_02023eb4(2) + (v - v)) != 0 ? -1 : 1;
    *(int *)(obj + 0x1c) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov273_020d175c);
}
