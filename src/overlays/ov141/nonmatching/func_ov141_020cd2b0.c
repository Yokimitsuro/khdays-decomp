/* NONMATCHING -- 180/180 B, and every instruction matches except ONE PAIR:
 * the ROM copies the 4-byte struct HIGH HALFWORD FIRST
 *     ldrh r0,[r2,#6] ; ldrh r2,[r2,#4] ; strh r0,[sp,#2] ; strh r2,[sp]
 * and mwcc emits low-first. Everything before and after is byte-identical.
 *
 * WORTH FINISHING: this is the head of a 7-member family (ov141/142/143 + 4 more,
 * 180 B each), so whatever fixes the pair pays 7 functions.
 *
 * Already solved on the way here, do not redo:
 *  - `hi |= 0x40` on the hw60 halfword must use the EXPLICIT extract/reassemble form,
 *    not the `struct hw60` bitfield: the bitfield adds an lsl#0x10/lsr#0x10 truncation
 *    pair (+8 B) that the ROM does not have. (`hi &= ~x` is the opposite -- it DOES
 *    want the bitfield. Same two forms back to back as in ov119 020ccef4.)
 *  - Ghidra called the second pool entry `DAT_arm9_ov141__020cd360`; the reloc says it
 *    is `func_ov141_020cd364`, a callback pointer passed to func_0203c634.
 *
 * Ruled out for the halfword pair:
 *  - assigning the two fields explicitly in ROM order (b then a): that also flips the
 *    register allocation and lands FURTHER away (diff moves 0x38 -> 0x21).
 *  - taking `&local` into a `struct pair *` first, to make the ROM's early `add r1,sp,#0`
 *    appear: +12 B.
 *  - the array-index spelling `*(struct pair *)&data[2]` over an `unsigned short[]` global
 *    (2026-07-18). That is the form used by func_ov131_020cdf20, which DOES emit the ROM's
 *    reversed `ldrh #6 ; ldrh #4` -- but there the copy is followed by a field overwrite
 *    (`buf.a = …`), and here both halves come from the data. Retried the reversed
 *    field-by-field assignment now that the hw60 form is fixed: worse (diff 0x38 -> 0x21).
 *    So the reversal seems to depend on a later partial overwrite, which this function
 *    does not have. */
struct pair { unsigned short a, b; };
extern void func_ov107_020c9264(int owner, int mode, int b);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_0203c634(int self, int index, void *cb);
extern char data_ov141_020ce9d0[];
extern void func_ov141_020cd364(void);

void func_ov141_020cd2b0(int self) {
    int *obj = *(int **)(self + 4);
    struct pair local;
    void (*cb)(int, struct pair *, int);

    func_ov107_020c9264(*obj, 4, 0);
    *(unsigned short *)(*obj + 0x1ae) |= 0x40;
    local = *(struct pair *)(data_ov141_020ce9d0 + 4);
    cb = *(void (**)(int, struct pair *, int))(*obj + 0x24);
    if (cb != 0) {
        cb(*obj, &local, 4);
    }
    func_ov107_020c9ee8(*(int *)(*obj + 0x3cc), 1, 0);
    {
        unsigned short v = *(unsigned short *)(*obj + 0x60);
        *(unsigned short *)(*obj + 0x60) =
            (unsigned short)((v & ~0xff00)
                             | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov141_020cd364);
}
