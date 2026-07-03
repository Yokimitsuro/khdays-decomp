/*
 * func_ov031_020b453c  (x4 family: ov031/ov050/ov070/ov088)  244 bytes
 *
 * Per-entry state dispatcher: iterate this->b19 entries (stride 0x1c8) and, per
 * entry->kind, either invoke handler-table data_ov031_020b4cd4[kind] (blx) or,
 * for kind==2, run func_ov031_020b4694 which may advance the entry to kind 4 —
 * in which case (if this owner is idle and no change yet this pass) it flags the
 * shared object for teardown (b47a=3/b47b=0), guarded by func_02030788 and an
 * object status bit.
 *
 * Byte-exact EXCEPT a 1-instruction register-coloring/hoist tie:
 *   - orig colors the per-iteration `entry` into r4 (lowest callee-saved), the
 *     owner-object ptr into r5, and HOISTS the handler-table base into fp
 *     (`ldr fp,[pc]` before the loop) => the dispatch load is `ldr r3,[fp,kind*4]`.
 *   - mwcc from any equivalent C colors obj->r4, pushes `entry` to r8, and uses
 *     fp to hold the constant 0 (reused for the two 0-args of func_02033d0c),
 *     loading the table base INLINE each pass (`ldr r0,[pc]`) => +1 instruction
 *     (248 bytes).
 * Tried: branch-inversion (kind!=2 first), struct-typed field access to kill the
 * LICM address-spill (this got it from 284->248), explicit table-base local ptr,
 * entry/kind hoisted to outer locals. None flip the fp allocation. Held-value-vs-
 * hoist class; unsteerable by source form. asm stub stays byte-exact.
 */
struct obj_t {
    unsigned int w0;               /* 0x000 */
    char _pad1[0x47a - 0x004];
    unsigned char b47a;            /* 0x47a */
    unsigned char b47b;            /* 0x47b */
    char _pad2[0x694 - 0x47c];
    unsigned char flag694 : 1;     /* 0x694 bit0 */
};

extern void (*data_ov031_020b4cd4[])(int this, int entry, int param2);
extern void func_ov031_020b4694(int this, int entry, int param2);
extern int func_02033d0c(int a, int b, int c, int d);
extern int func_02030788(void);

void func_ov031_020b453c(int this, int param2) {
    struct obj_t *obj = *(struct obj_t **)(this + 8);
    int changed = 0;
    int off = 0;
    int i = 0;

    if ((int)(unsigned char)*(char *)(this + 0x19) <= 0) return;
    do {
        int entry = *(int *)(this + 0xc) + off;
        int kind = *(signed char *)(entry + 2);
        if (kind != 0) {
            if (kind != 2) {
                data_ov031_020b4cd4[kind](this, entry, param2);
            } else {
                func_ov031_020b4694(this, entry, param2);
                if (*(signed char *)(entry + 2) == 4 && *(int *)this == 0 && changed == 0) {
                    if (obj->flag694) {
                        func_02033d0c(0xcb, 0, entry + 0xcc, 0);
                    }
                    if (func_02030788() == 0 && (obj->w0 & 0x10000) == 0) {
                        obj->b47a = 3;
                        obj->b47b = 0;
                    }
                    changed = 1;
                }
            }
        }
        off += 0x1c8;
        i++;
    } while (i < (int)(unsigned char)*(char *)(this + 0x19));
}
