/* NONMATCHING (4-byte constant-materialization scheduling tie): all the semantic ops
 * match — the two hw60 hi-byte edits (|=1 explicit no-trunc, &=~0x8c bitfield-with-trunc),
 * the b8 |=1, the vec copy. Only the 0x1000 constant differs: the ROM hoists `mov ip,#0x1000`
 * into the ldrh load-use stall (early) and keeps it in ip (`mov r0,ip` + `str ip` late, 212B),
 * whereas mwcc materializes it directly into r0 at the store/call (208B). Resisted a `scale`
 * local, an early obj[8] store (size matched at 212 but swapped ip/lr + moved the store), and
 * a `dst` pointer local.
 *
 * c634 handler: reset obj[9]/obj[10], set owner hw60 hi bit 1 then clear bits 0x8c, set
 * bit0 of the low byte at *(owner+0x388)+8, copy the owner's facing vec (owner+0x394) into
 * obj[5..7] with obj[8]=0x1000 scale, run func_01ffa724 (scale the vec into obj[2..4]),
 * and dispatch via func_0203c634. */
struct hw60 { unsigned short lo:8, hi:8; };
struct b8 { unsigned int b:8; };
struct vec { int x, y, z; };
extern void func_01ffa724(int scale, int *v, unsigned int *out);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov137_020cef68(void);
void func_ov137_020cee94(int self) {
    int *obj = *(int **)(self + 4);
    int *dst = obj + 5;
    int scale = 0x1000;
    obj[9] = 0;
    obj[10] = 0;
    {
        unsigned short v = *(unsigned short *)(*obj + 0x60);
        *(unsigned short *)(*obj + 0x60) =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    }
    ((struct hw60 *)(*obj + 0x60))->hi &= ~0x8c;
    ((struct b8 *)(*(int *)(*obj + 0x388) + 8))->b |= 1;
    *(struct vec *)dst = *(struct vec *)(*obj + 0x394);
    obj[8] = scale;
    func_01ffa724(scale, dst, (unsigned int *)(obj + 2));
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov137_020cef68);
}
