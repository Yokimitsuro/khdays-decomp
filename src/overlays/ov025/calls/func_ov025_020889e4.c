/* Copy up to two (index, value) pairs from an object into a subitem table: the indices live at
 * +0x14 and the values at +0x34, or at +0x3c when the alternate set is asked for. A pair is
 * applied only when the object is present and neither half is -1.
 *
 * Parked as a strength-reduction tie with "tried induction/array-index/held-base/merged-condition
 * spellings; none suppress the reduction". Declaring the two runs as real arrays inside a struct
 * does suppress it: mwcc then keeps the counter live and scales it inline, instead of seeding and
 * stepping two walking pointers and spending two extra callee-saved registers. */
extern void func_02032634(int target, int index, unsigned int value);

struct Ov008SubitemRow {
    char _pad0[0x14];
    int idx[2];
    char _pad1[0x18];
    int val[2];         /* +0x34 */
    int alt[2];         /* +0x3c */
};

void func_ov025_020889e4(int target, struct Ov008SubitemRow *obj, int useAlt) {
    unsigned int *base;
    int index;
    int i;
    if (useAlt != 0) base = (unsigned int *)obj->alt;
    else base = (unsigned int *)obj->val;
    for (i = 0; i < 2; i++) {
        unsigned int value = base[i];
        if (obj != 0 && (index = obj->idx[i]) != -1 && value != 0xffffffff) {
            func_02032634(target, index, value);
        }
    }
}
