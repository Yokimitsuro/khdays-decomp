/* NONMATCHING: semantics correct, arg-materialization scheduling tie. The ROM
 * computes &buf (the callback's 2nd arg) right after the f40 guard; mwcc 3.0/139
 * places it just before the blx (or, with a helper pointer, before the guard) — a
 * 1-instruction position shift, same size. Not steerable from C.
 */
/* c634 handler: set obj->f14 = self->f0->f2c*30/5; bail if obj->f40 >= 0x100. Copy
 * two shorts from data_ov137_020cf37c (+0xc/+0xe) into a stack buffer and invoke the
 * owner's callback (owner->+0x24)(owner, buf, 4) if present. Then obj->f14 =
 * self->f0->f2c*30/10, func_ov107_020c9264(owner,6,0), clear obj->f3c/f54, dispatch. */
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov137_020cd8b4(void);
extern unsigned short data_ov137_020cf37c[];
void func_ov137_020cd7e8(int self) {
    int obj = *(int *)(self + 4);
    unsigned short buf[2];
    void (*cb)(int owner, void *b, int c);
    *(int *)(obj + 0x14) = *(int *)(*(int *)self + 0x2c) * 30 / 5;
    if (*(int *)(obj + 0x40) >= 0x100) {
        return;
    }
    buf[1] = data_ov137_020cf37c[7];
    buf[0] = data_ov137_020cf37c[6];
    cb = *(void (**)(int, void *, int))(*(int *)obj + 0x24);
    if (cb != 0) {
        cb(*(int *)obj, buf, 4);
    }
    *(int *)(obj + 0x14) = *(int *)(*(int *)self + 0x2c) * 30 / 10;
    func_ov107_020c9264(*(int *)obj, 6, 0);
    *(int *)(obj + 0x3c) = 0;
    *(unsigned char *)(obj + 0x54) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov137_020cd8b4);
}
