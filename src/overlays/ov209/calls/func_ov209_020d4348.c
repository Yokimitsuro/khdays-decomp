/* c634 handler (charge-then-break variant): while obj->f49==0, charge obj->f2c by
 * self->f0->f2c; at >=0x99a fire func_ov107_020c5af8(owner, 0x154, 4, owner->f3c4+4)
 * and latch f49=1. Bail if *(obj->f4 + 0xad) is set. Clear owner->+0x1ae bit0, set
 * bit0 of owner->f3b8->+8 and f3b4->+8, func_ov107_020c9264(owner, 6, 1), reset
 * obj->f2c, dispatch via func_0203c634. owner re-read per section. */
extern void func_ov107_020c5af8(int owner, int a, int b, int c);
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov209_020d4448(void);
struct b8 { unsigned int f:8; };
void func_ov209_020d4348(int self) {
    int obj = *(int *)(self + 4);
    if (*(unsigned char *)(obj + 0x49) == 0) {
        int acc = *(int *)(obj + 0x2c) + *(int *)(*(int *)self + 0x2c);
        *(int *)(obj + 0x2c) = acc;
        if (acc >= 0x99a) {
            func_ov107_020c5af8(*(int *)obj, 0x154, 4, *(int *)(*(int *)obj + 0x3c4) + 4);
            *(unsigned char *)(obj + 0x49) = 1;
        }
    }
    if (*(unsigned char *)(*(int *)(obj + 4) + 0xad) != 0) {
        return;
    }
    *(unsigned short *)(*(int *)obj + 0x1ae) &= ~1;
    ((struct b8 *)(*(int *)(*(int *)obj + 0x3b8) + 8))->f |= 1;
    ((struct b8 *)(*(int *)(*(int *)obj + 0x3b4) + 8))->f |= 1;
    func_ov107_020c9264(*(int *)obj, 6, 1);
    *(int *)(obj + 0x2c) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov209_020d4448);
}
