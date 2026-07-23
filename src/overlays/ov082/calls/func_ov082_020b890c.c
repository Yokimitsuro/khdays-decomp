/* Dispatch the two handled selectors: install the sub-object handler for the
 * requested selector and hand back the follow-up step, or NULL for anything else.
 *
 * The residue this had for a long time was "the ROM materialises the return 0 in r0
 * before the comparisons". It is not a predication tie: with a `void *r = 0;` that is
 * assigned in each case and returned ONCE at the end, the zero is live on every path
 * and mwcc emits the same unconditional `mov r0,#0` in the compare/branch gap. The
 * `base` pointer must still be declared FIRST -- declaring the result first swaps the
 * `add` and the `cmp`.
 *
 * One of four byte-identical siblings (ov044/ov063/ov082/ov099). */
struct Outer;
extern void func_ov082_020b9ff0(struct Outer *outer, int sel);
extern void func_ov082_020b8970(void);
extern void func_ov082_020b8984(void);

void *func_ov082_020b890c(struct Outer *obj, int a) {
    struct Outer *base = (struct Outer *)((char *)obj + 0xa8);
    void *r = 0;
    switch (a) {
    case 0x22:
        func_ov082_020b9ff0((struct Outer *)((char *)base + 0x2c00), 0x22);
        r = (void *)func_ov082_020b8970;
        break;
    case 0x23:
        func_ov082_020b9ff0((struct Outer *)((char *)base + 0x2c00), 0x23);
        r = (void *)func_ov082_020b8984;
        break;
    }
    return r;
}
