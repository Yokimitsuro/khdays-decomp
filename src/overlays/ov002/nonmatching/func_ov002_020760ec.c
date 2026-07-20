/* NONMATCHING -- everything outside the four-slot init loop is byte-identical.
 * Confirmed by reading the diff to the end: from the loop onward the two streams
 * are the SAME instructions, offset by exactly one line, and the tail realigns
 * perfectly. Total size is 132 either way; my loop is one instruction (2 bytes)
 * shorter and the literal-pool padding absorbs it.
 *
 * The single residue: the ROM COPIES the counter to a scratch register before
 * incrementing it, then stores the copy.
 *
 *      ROM                          mwcc (every form below)
 *      adds r2, r4, #0   ; slot     adds r0, r4, #0   ; slot
 *      adds r0, r1, #0   ; copy i   movs r1, #0       ; i
 *      adds r1, r1, #1   ; i++      str  r1, [r0, #0x6c]
 *      str  r0, [r2, #0x6c]         adds r1, r1, #1
 *      adds r2, r2, #4              adds r0, r0, #4
 *
 * So the ROM spends an extra instruction that -O4 has no reason to spend, which
 * says the source forced it -- and it also parks `slot` in r2 rather than the
 * lowest free register. The two are probably one cause, not two.
 *
 * Ruled out 2026-07-20, nine forms, none closer than the above:
 *   1. ((int *)(self + 0x6c))[i] = i            -- folds the base, emits stm r1!,{r0}
 *   2. *(int *)(self + i * 4 + 0x6c) = i        -- keeps a byte index, recomputes self+i
 *   3. int *slot walking by ++, i declared first
 *   4. same, declarations swapped
 *   5. char *slot walking by 4                  -- closest shape, slot still in r0
 *   6. same, slot initialised before the 0x64 store
 *   7. do { *(int *)(slot + 0x6c) = i++; slot += 4; } while (i < 4)
 *   8. explicit v = i; i++; store v             -- the literal transcription; still no copy
 *   9. a struct with int nSlots[4] at 0x6c, indexed s->nSlots[i] = i
 *
 * THE CORPUS SEARCH WAS RUN, AND IT DID NOT PAY -- do not repeat it.
 * `python tools/find_insn.py --seq 'adds r\d+, r\d+, #0' 'adds r\d+, r\d+, #1'`
 * returns exactly TWO matched functions. The promising one, func_ov022_0209016c,
 * has the identical instruction shape (copy, increment, store at a displacement)
 * and its source is the clean walking-pointer loop:
 *
 *     q = (int *)obj;
 *     for (i = 0; i < 15; i++) { q[6] = 0; q++; }
 *
 * But that loop stores a CONSTANT, not the counter -- so its copy cannot be the
 * counter being preserved across its own increment, and the form does not carry
 * over. Form 3 above is already that exact shape and still emits no copy. So the
 * corpus contains no known-good C that produces this, which is a real negative
 * and worth having.
 *
 * NEXT LEVER, still untried: the copy and the r2 placement are probably one
 * cause. Something must be keeping the counter live past its increment -- an
 * aliasing barrier, or the stored value being a second variable mwcc coalesces
 * in our version but the original kept distinct (try making the stored value a
 * `short`/`char` widened on store, or storing through a volatile destination).
 * Not build-swept: a nine-form search is not exhausted enough for a sweep to mean
 * anything, and the compiler is not the suspect for a single scratch copy. */
typedef struct {
    char _0[0x6c];
    int nSlots[4];
} Ov002Module;

extern int data_ov002_0207fa20;
extern int data_ov002_0207f468;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);
extern void func_02030cf8(int id, void *handler);
extern void func_ov002_0207605c(void);
extern void func_ov002_0207682c(void);
extern int func_02024ee8(int archive, int mode);
extern void func_ov002_0206da54(int channel, int handle);
extern void func_ov002_020761d8(void);

void *func_ov002_020760ec(void) {
    char *self = (char *)NNSi_FndGetCurrentRootHeap();
    int i;

    (&data_ov002_0207fa20)[1] = (int)self;
    MI_CpuFill8(self + 0x17c, 0, 0x80);
    func_02030cf8(5, (void *)&func_ov002_0207605c);

    *(int *)(self + 0x64) = 0x1000;
    for (i = 0; i < 4; i++) {
        ((Ov002Module *)self)->nSlots[i] = i;
    }

    func_ov002_0207682c();
    self[0x68] = 0;

    *(int *)(self + 0x60) = func_02024ee8((int)&data_ov002_0207f468, 3);
    func_ov002_0206da54(1, *(int *)(self + 0x60));

    *(char *)((&data_ov002_0207fa20)[1] + 0x260) = -1;
    MI_CpuFill8(self + 0x200, 0, 0x60);

    return (void *)&func_ov002_020761d8;
}
