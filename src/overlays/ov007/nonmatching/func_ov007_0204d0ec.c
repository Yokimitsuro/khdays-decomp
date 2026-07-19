/* UNFINISHED. 132/132 bytes, 33/33 instructions.  ov007 is now 13/14 and this is the
 * LAST function standing between it and 100%.
 *
 * The whole diff is TWO predicated instructions swapped in the empty-line branch:
 *      ROM:   streq r0,[r4,#0x20]  ;  ldreq r2,[pc,#0x34]      (store, then load)
 *      mine:  ldreq r2,[pc,#0x38]  ;  streq r0,[r4,#0x20]
 * Everything else -- both arms, the B-button block, the 0 hoisted into r0 and reused by
 * all three stores, `ret` living in r2 -- is identical.
 *
 * RULED OUT (the last three prove the structure below is right, so do not repeat them):
 *   the else branch's two statements written in the other order   -> same diff at 0x34
 *   the shared `root->frame = 0` hoisted out of both arms         -> 128 B, 4 SHORT
 *   the test negated so the empty-line case is the `if`           -> 140 B, 8 OVER
 *   * 2026-07-20: full TYPING pass -- real struct for the context and a real function
 *     pointer for the return value (returning a handler was load-bearing for the
 *     ov032/ov052/ov072 family the same day).  Same diff at 0x34.  Kept below anyway
 *     because it is far better C for the port.
 *
 * An earlier note claimed "no mwcc generation matches (verify_sweep)".  Treat that as a
 * prior, not a verdict: 14k functions match byte-exactly with this exact compiler, so a
 * build difference is the least likely explanation, not the first.
 *
 * NOTE its sibling func_ov007_0204ce94 WAS cracked on 2026-07-20 by the array-indexing
 * crack, after carrying an equally confident "mwcc does not reproduce this" note.  The
 * lever there was reading the index through the struct field (`base[b->cursor]`) instead
 * of a cached local, which is what stopped mwcc CSEing two identical loads.  Nothing
 * analogous is left here -- the two instructions are already in the right registers -- but
 * that is exactly what the ce94 note said too.
 */
typedef int (*Ov007Handler)(void);

typedef struct {
    char pad00[0x20];
    int frame;                /* +0x20 */
    char pad24[0x4c];
    int lineCount;            /* +0x70 */
    char pad74[0x8];
    unsigned short line[1];   /* +0x7c */
} Ov007Ctx;

extern Ov007Ctx *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov007_0204ce94(void *p);
extern int func_ov007_0204d170(void);
extern int func_ov007_0204cf7c(void);
extern int func_ov007_0204d2d0(void);
extern unsigned short data_0204c190;

Ov007Handler func_ov007_0204d0ec(void) {
    Ov007Ctx *root = NNSi_FndGetCurrentRootHeap();
    Ov007Handler ret = 0;
    int frame = root->frame + 1;

    root->frame = frame;
    if (frame >= 0xf) {
        func_ov007_0204ce94(root);
        if (root->line[0] != 0) {
            root->lineCount = root->lineCount + 1;
            ret = func_ov007_0204cf7c;
            root->frame = 0;
        } else {
            root->frame = 0;
            ret = func_ov007_0204d170;
        }
    }
    if ((data_0204c190 & 8) != 0) {
        root->frame = 0;
        ret = func_ov007_0204d2d0;
    }
    return ret;
}
