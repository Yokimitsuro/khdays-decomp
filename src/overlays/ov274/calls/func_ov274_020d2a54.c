/* c634 handler: once obj->f52 is still 0, accumulate obj->f24 += self->f0->f2c;
 * on reaching 0x999 fire func_ov107_020c5af8(owner, 0x163, 7, owner->f3bc+4) and
 * latch obj->f52 = 1. Bail if *(obj->fc) byte is set. Then clear owner->+0x1ae bit
 * 0, set bit 0 of owner->f3ac->+8 and owner->f3b0->+8 low bytes,
 * func_ov107_020c9264(owner, 8, 1), reset obj->f24, and dispatch via func_0203c634.
 * owner re-read per section. self->+0x20 = slot index. */
extern void func_ov107_020c5af8(int owner, int a, int b, int c);
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov274_020d2b58(void);
struct b8 { unsigned int f:8; };
void func_ov274_020d2a54(int self) {
    int obj = *(int *)(self + 4);
    if (*(unsigned char *)(obj + 0x52) == 0) {
        int f24 = *(int *)(obj + 0x24) + *(int *)(*(int *)self + 0x2c);
        *(int *)(obj + 0x24) = f24;
        if (f24 >= 0x999) {
            func_ov107_020c5af8(*(int *)obj, 0x163, 7, *(int *)(*(int *)obj + 0x3bc) + 4);
            *(unsigned char *)(obj + 0x52) = 1;
        }
    }
    if (*(unsigned char *)(*(int *)(obj + 0xc)) != 0) {
        return;
    }
    *(unsigned short *)(*(int *)obj + 0x1ae) &= ~1;
    ((struct b8 *)(*(int *)(*(int *)obj + 0x3ac) + 8))->f |= 1;
    ((struct b8 *)(*(int *)(*(int *)obj + 0x3b0) + 8))->f |= 1;
    func_ov107_020c9264(*(int *)obj, 8, 1);
    *(int *)(obj + 0x24) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov274_020d2b58);
}
