/* Enter the recovery/stagger state (x3: ov212/266/267). Drop bit 0 of the hw60 hi byte,
 * raise flags 3 on the owner's +0x1ae word, then raise flags 0x86 on that same hw60 hi
 * byte, release the 3 tracked sub-objects, kick the 0x4d animation and advance state.
 *
 * NOTE the two hw60 writes need OPPOSITE C forms, and the disassembly is what says so:
 * the `&= ~1` at +0x014 HAS the lsl#0x10/lsr#0x10 trunc pair -> bitfield form; the
 * `|= 0x86` at +0x054 does NOT -> explicit extract/reassemble. Same shape as
 * func_ov231_020cf578. Never infer the form from the operator. */
extern void func_ov107_020c5af8(int a, int b, int c, void *d);
extern void func_ov212_020ce404(int a);
extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov212_020d0700(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };

void func_ov212_020d0620(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    int i = 0;
    unsigned short v;

    ((struct hw60 *)(*ctx + 0x60))->hi &= ~1;
    *(unsigned short *)(*ctx + 0x1ae) |= 3;
    v = *(unsigned short *)(*ctx + 0x60);
    *(unsigned short *)(*ctx + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10));
    for (; i < 3; i++) {
        ((struct b8 *)(((int *)*ctx)[i + 0x133] + 8))->f &= ~1;
    }
    func_ov107_020c5af8(*ctx, 0, 0x4d, (void *)(*ctx + 0x74));
    func_ov212_020ce404((int)ctx);
    func_0203c634(self, *(signed char *)((char *)self + 0x20), func_ov212_020d0700);
}
