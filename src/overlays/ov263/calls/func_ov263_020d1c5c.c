/* c634 state-entry handler: clear obj->f28, run func_ov263_020d0628(self), then
 * bias obj->f1c/f18 by +/-0xc91 depending on obj->f49, push the animation frame
 * (obj->f49 + 4) to owner->f388 and owner (func_ov107_020c9ee8 / _020c9264). If
 * obj->f49 >= 2, recompute f1c/f18 from func_020050b4(obj->f14->f19c, ->f1a4) and
 * push frame 5. Then func_ov107_020c5af8(owner, obj->f50, 4, obj->f8), set bit 1 of
 * the owner->f3bc->+8 low byte, and dispatch via func_0203c634. owner re-read per
 * section. self->+0x20 = slot index. */
extern void func_ov263_020d0628(int self);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_ov107_020c9264(int owner, int a, int b);
extern int func_020050b4(int a, int b);
extern void func_ov107_020c5af8(int owner, int a, int b, int c);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov263_020d1d6c(void);
struct b8 { unsigned int f:8; };
void func_ov263_020d1c5c(int self) {
    int obj = *(int *)(self + 4);
    int v;
    *(int *)(obj + 0x28) = 0;
    func_ov263_020d0628(self);
    v = *(int *)(obj + 0x1c) + (*(unsigned char *)(obj + 0x49) == 0 ? 0xc91 : -0xc91);
    *(int *)(obj + 0x1c) = v;
    *(int *)(obj + 0x18) = v;
    func_ov107_020c9ee8(*(int *)(*(int *)obj + 0x388), *(unsigned char *)(obj + 0x49) + 4, 0);
    func_ov107_020c9264(*(int *)obj, *(unsigned char *)(obj + 0x49) + 4, 0);
    if (*(unsigned char *)(obj + 0x49) >= 2) {
        v = func_020050b4(*(int *)(*(int *)(obj + 0x14) + 0x19c), *(int *)(*(int *)(obj + 0x14) + 0x1a4)) + -6434;
        *(int *)(obj + 0x1c) = v;
        *(int *)(obj + 0x18) = v;
        func_ov107_020c9ee8(*(int *)(*(int *)obj + 0x388), 5, 0);
        func_ov107_020c9264(*(int *)obj, 5, 0);
    }
    func_ov107_020c5af8(*(int *)obj, *(short *)(obj + 0x50), 4, *(int *)(obj + 8));
    {
        int tmp = *(int *)(*(int *)obj + 0x3bc);
        ((struct b8 *)(tmp + 8))->f |= 2;
    }
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov263_020d1d6c);
}
