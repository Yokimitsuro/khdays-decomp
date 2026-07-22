/* Push up to two subitem values into the table -- from the +0x44 run when the alternate set is
 * asked for, from +0x34 otherwise -- skipping entries whose index (+0x14) or value is -1; then
 * record which run was used in bit 0 of +0x84.
 *
 * Two things the park was missing. The three runs have to be real arrays in a struct, or mwcc
 * strength-reduces `obj + i*4` into walking pointers instead of computing the row pointer once
 * and reaching the three fields by displacement. And the trailing flag write is a ONE-BIT
 * BITFIELD, not a hand-written read-modify-write: `flags = (flags & ~1) | (x != 0)` is one
 * instruction short, because a bitfield store masks the incoming value with 1 first
 * (`and r0,r0,#1`) before the bic/orr, and mwcc knows a hand-rolled boolean is already 0 or 1. */
extern void func_02032634(int target, int index, unsigned int value);

struct Ov008SubitemBlock {
    char _pad0[0x14];
    int idx[2];
    char _pad1[0x18];
    unsigned int val[2];        /* +0x34 */
    char _pad2[8];
    unsigned int alt[2];        /* +0x44 */
    char _pad3[0x84 - 0x4c];
    unsigned int bUseAlt : 1;   /* +0x84 bit 0 */
};

void func_ov025_020887c0(int target, struct Ov008SubitemBlock *obj, int useAlt) {
    int i = 0;
    do {
        int index = obj->idx[i];
        if (index != -1) {
            if (useAlt != 0) {
                unsigned int v = obj->alt[i];
                if (v != 0xffffffff) func_02032634(target, index, v);
            } else {
                unsigned int v = obj->val[i];
                if (v != 0xffffffff) func_02032634(target, index, v);
            }
        }
        i++;
    } while (i < 2);
    obj->bUseAlt = (useAlt != 0);
}
