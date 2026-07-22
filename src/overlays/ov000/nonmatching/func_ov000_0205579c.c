/* func_ov000_0205579c -- build a menu widget from its descriptor and append it to the screen's
 * list. Returns the new object, or NULL if the heap is out.
 *
 * The descriptor's flag word at +0x50 drives everything:
 *   bit 0 -- pick which of the two coordinate pairs the two sub-slots are keyed off: the pair at
 *            +0x18 normally, or the one at +0x8 when BOTH of the +0x18 values are negative
 *            (i.e. unset). Without the bit it is always +0x8, and the object's own bit 0 is
 *            cleared instead of set.
 *   bit 2 -- the widget is a two-point one: func_ov000_02055c48 lays it out between +0x20 and
 *            +0x30 with a 0x3e8 span, and the +0x28 pair is copied in. Otherwise
 *            func_ov000_02055bfc places it at +0x30 alone.
 *   bit 1 / bit 4 -- run func_02032710(.., 0) / func_02032760(.., 1) over the live sub-slots.
 *   bit 3 -- copied straight through to the object's own bit 3.
 *
 * Each of the two sub-slots is registered via WM_EndKeySharing_0x02032444 unless its key is
 * negative, in which case the slot is marked -1 and skipped. Its priority is
 * (unsigned char)(desc[0x54] + 1 - i), so slot 0 outranks slot 1.
 *
 * ------------------------------------------------------------------------------------------
 * NONMATCHING: 648/648, same instructions in the same order and the same block layout. The
 * residue is a uniform ONE-REGISTER ROTATION of the callee-saved set:
 *     ROM   obj=r4  i=r5  keys=r6  desc=r7  self=r8  base=sb  -1=sl
 *     mine  -1=r4   obj=r5 ...                       desc=sb  self=sl
 * Both push the identical register set; mwcc simply hands r4 to a temporary before obj.
 *
 * !! THE PREVIOUS NOTE'S DIAGNOSIS IS RETRACTED. It read:
 *     "ROM: three separate `mvn` of -1, one per loop / mine: ONE hoisted -1 shared across the
 *      whole function, and it takes r4 ... Retry only with a way to stop the -1 CSE."
 * That CSE is GONE. Rewriting the object as ONE struct typed on the parameter (the
 * func_ov000_020552b4 lever, commit 110af975) instead of inline casts off an `int self` makes
 * mwcc materialise -1 three times, exactly like the ROM -- confirmed by disassembly, three
 * `mvn` on each side. So the stated blocker no longer exists, and the rotation survives it.
 * Anyone retrying should NOT go hunting the CSE; it is not there any more.
 *
 * Also worth knowing, because it is the opposite of what the old note concluded: the `base`
 * local (self + 0x4000) is NOT needed once the parameter is typed. Adding it back on top of the
 * struct changes nothing -- 100 differing lines either way. The ROM's repeated address add is a
 * consequence of the offsets exceeding the 12-bit ldr immediate, not an idiom to imitate.
 *
 * Ruled out for the rotation, all leaving exactly 100 differing lines: obj initialised in its
 * own declaration; `keys` declared before `i`; the base local restored (both with the style
 * field read through it and through the struct). Giving the -1 its own named local is worse --
 * 636 bytes, 142 lines.
 *
 * Everything else was steered successfully and must be kept:
 *   - the NULL return has to fall into the shared `mov r0,r4 ; pop` (guard written `!= 0`);
 *   - the loop uses the word-index form (`((int *)obj)[i + 0xd]`), or mwcc strength-reduces to a
 *     walking pointer;
 *   - the keys select is written `>= 0 ||` so the +0x18 arm is emitted first (addge before
 *     addlt); the `!(a < 0 && b < 0)` form gives the same test with the arms swapped.
 *
 * Do not re-derive the semantics; they are settled. */

typedef struct {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short offset;
} NNSFndList;

typedef struct {
    unsigned b0 : 1;
    unsigned b1 : 1;
    unsigned b2 : 1;
    unsigned b3 : 1;
} Flags84;

typedef struct {
    char reserved[0x4a38];
    NNSFndList children;         /* +0x4a38 */
    char reserved2[0x2c];
    int focused;                 /* +0x4a70 */
    int style;                   /* +0x4a74 */
} Root;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void *MI_CpuFill8(void *dst, unsigned char v, unsigned int n);
extern void *MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void func_02035f84(void *p);
extern int WM_EndKeySharing_0x02032444(Root *self, int key, int a);
extern void func_020325b8(Root *self, int slot, int prio);
extern void func_02032680(Root *self, int slot, int a);
extern void func_ov000_02055c48(Root *self, void *obj, int n, void *a, void *b, int span);
extern void func_ov000_02055bfc(Root *self, void *obj, void *a);
extern void func_02032710(Root *self, int slot, int a);
extern void func_02032760(Root *self, int slot, int a);
extern void NNS_FndAppendListObject(NNSFndList *list, void *obj);

void *func_ov000_0205579c(Root *self, char *desc) {
    char *obj;
    int i;
    char *keys;
    obj = NNSi_FndAllocFromDefaultExpHeap(0x9c);
    if (obj != 0) {
        MI_CpuFill8(obj, 0, 0x9c);
        *(int *)(obj + 0xc) = *(int *)desc;
        func_02035f84(obj + 0x4c);
        func_02035f84(obj + 0x68);

        if (*(int *)(desc + 0x50) & 1) {
            /* Written the `>= 0 ||` way round so the +0x18 arm is emitted first (addge before
             * addlt), matching the ROM; it compiles to the same short-circuit test as
             * `!(a < 0 && b < 0)` but puts the arms in the other order. */
            if (*(int *)(desc + 0x18) >= 0 || *(int *)(desc + 0x1c) >= 0) {
                keys = desc + 0x18;
            } else {
                keys = desc + 8;
            }
            ((Flags84 *)(obj + 0x84))->b0 = 1;
        } else {
            keys = desc + 8;
            ((Flags84 *)(obj + 0x84))->b0 = 0;
        }

        for (i = 0; i < 2; i++) {
            ((int *)obj)[i + 0xd] = ((int *)desc)[i + 2];
            ((int *)obj)[i + 0xf] = ((int *)desc)[i + 4];
            ((int *)obj)[i + 0x11] = ((int *)desc)[i + 6];

            if (((int *)keys)[i] < 0) {
                ((int *)obj)[i + 5] = -1;
                continue;
            }

            ((int *)obj)[i + 5] =
                WM_EndKeySharing_0x02032444(self, ((int *)keys)[i], *(int *)(desc + 4));
            func_020325b8(self, ((int *)obj)[i + 5], (unsigned char)(*(int *)(desc + 0x54) + 1 - i));
            func_02032680(self, ((int *)obj)[i + 5], self->style);
        }

        *(int *)(obj + 0x10) = *(int *)(desc + 4);
        *(unsigned short *)(obj + 0x1c) = *(unsigned short *)(desc + 0x38);
        *(unsigned short *)(obj + 0x1e) = *(unsigned short *)(desc + 0x3a);
        *(int *)(obj + 0x20) = *(int *)(desc + 0x3c);

        if (*(int *)(desc + 0x50) & 4) {
            func_ov000_02055c48(self, obj, 2, desc + 0x20, desc + 0x30, 0x3e8);
            MI_CpuCopy8(desc + 0x28, obj + 0x24, 8);
            *(int *)(obj + 0x84) |= 4;
        } else {
            func_ov000_02055bfc(self, obj, desc + 0x30);
            *(int *)(obj + 0x84) &= ~4;
        }
        MI_CpuCopy8(desc + 0x30, obj + 0x2c, 8);

        if (*(int *)(desc + 0x50) & 2) {
            for (i = 0; i < 2; i++) {
                if (((int *)obj)[i + 5] != -1) {
                    func_02032710(self, ((int *)obj)[i + 5], 0);
                }
            }
            *(int *)(obj + 0x84) &= ~2;
        } else {
            *(int *)(obj + 0x84) |= 2;
        }

        if (*(int *)(desc + 0x50) & 0x10) {
            for (i = 0; i < 2; i++) {
                if (((int *)obj)[i + 5] != -1) {
                    func_02032760(self, ((int *)obj)[i + 5], 1);
                }
            }
        }

        ((Flags84 *)(obj + 0x84))->b3 = (*(int *)(desc + 0x50) & 8) != 0;
        NNS_FndAppendListObject(&self->children, obj);
    }

    return obj;
}
