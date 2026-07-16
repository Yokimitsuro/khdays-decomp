/* func_ov232_020d31b8 -- acquire a target and arm the state, or give up if there is none.
 *
 * func_ov107_020cab14(ctx[0], 0) picks the target. With none, ctx[0]+0x1c7 is cleared and the
 * object re-enters with no callback. With one, the squared distance from ctx[0]+0xb0 to
 * target+0x190 is cached at +0x14, the two counters at +0x1c/+0x20 are zeroed, the flags are
 * updated and effect 5 fires before handing off to func_ov232_020d32ac.
 *
 * ★ The two hw60 writes here are the catalog's discriminator sitting back to back in one
 * function, and they need OPPOSITE C forms (see codegen-cracks.md):
 *   - `hi |= 1` has NO `lsl#0x10 ; lsr#0x10` trunc pair in the ROM -> explicit extract/reassemble,
 *     with `v & ~0xff00` (bic) for the lo-byte keep;
 *   - `hi &= ~0x8c` DOES have the trunc pair -> the bitfield form.
 * Reading the pair off the disassembly is the whole trick; do not guess from the operator. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

extern int func_ov107_020cab14(int owner, int a);
extern void func_0203c634(int self, int action, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(const VecFx32 *a, const VecFx32 *b);
extern void func_ov107_020c5af8(int owner, int a, int b, int ptr);
extern void func_ov232_020d32ac(void);

void func_ov232_020d31b8(int self) {
    int *ctx;
    VecFx32 d;
    int target;
    unsigned short v;

    ctx = *(int **)(self + 4);
    target = func_ov107_020cab14(ctx[0], 0);
    if (target == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 0;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    VEC_Subtract((const VecFx32 *)(target + 0x190), (const VecFx32 *)(ctx[0] + 0xb0), &d);
    ctx[5] = func_01ff8d18(&d, &d);
    ctx[8] = 0;
    ctx[7] = 0;

    v = *(unsigned short *)(ctx[0] + 0x60);
    *(unsigned short *)(ctx[0] + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));

    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x8c;

    *(unsigned char *)((char *)ctx + 0x26) = 0;
    func_ov107_020c5af8(ctx[0], *(short *)((char *)ctx + 0x24), 5, ctx[1]);
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov232_020d32ac);
}
