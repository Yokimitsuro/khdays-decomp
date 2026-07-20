/* func_ov045_020b476c -- build the two-stage emitter descriptor and install it.
 *
 * NONMATCHING: 324/328 bytes, and the entire difference is ONE INSTRUCTION at the very end.
 * Every one of the 34 field stores, every constant, the whole 0xa0-byte descriptor and all
 * five calls are byte-exact.
 *
 * SEMANTICS: allocate a 0x30-byte object, park it at self+0x2644, and initialise it.  The
 * descriptor handed to func_ov022_02091298 is an array of TWO 0x50-byte stages with the
 * same layout, differing only in five fields -- the id (0x1e1 / 0x3e1), a rate (0x800 /
 * 0xccd), and three tail values (5/0x25, 2/3, 0x1333/0x2000).  Everything else, including
 * the 0xa000 / 0x12000 pair, the 0x100 pair and the 0x300, is identical between the stages.
 * Finally the two callbacks at +0x20 / +0x24 of the new object are installed.
 *
 * THE DIFFERENCE: the two stack arguments of the big call.
 *      ROM   str r2, [sp] ; str r1, [sp, #4]
 *      ours  stm sp, {r0, r2}
 * The ROM re-uses the registers that already hold 2 and 0xa from the field stores at +0x44
 * and +0x54; we materialise them fresh into r0/r2, which lets mwcc merge the pair into a
 * store-multiple and saves the 4 bytes.
 *
 * Both shapes exist in matched code -- 108 functions emit the two separate stores and 29
 * emit `stm sp, ...` -- so this is steerable in principle.  The matched stm cases pass
 * incoming PARAMETERS straight through (they are already in registers); the two-str cases
 * pass computed or mixed values.  Here both are small constants, which is the case that
 * merges.
 *
 * RULED OUT (all still 324):
 *   the two constants hoisted into locals used both for the fields and the call arguments,
 *     which is exactly what the ROM's register re-use looks like;
 *   those two field stores moved to immediately before the call;
 *   deriving 0x3e1 from the member holding 5 and 0xccd from the member holding 0x1333 --
 *     that is 320, four bytes WORSE, because mwcc folds through the store.  Note the ROM
 *     folds too: its `add r0, r2, #0x3dc` and `rsb r0, r0, #0x2000` are cheap
 *     materialisations of 0x3e1 and 0xccd from constants it already has live, not
 *     source-level derivations.  I misread them as the opposite at first; the ov301 park
 *     documents the genuinely opposite case, where the ROM does NOT fold.
 *   assigning d[0].f38 = 5 early so 5 is the constant materialised first: also 320.
 *
 * NEXT STEP: find what stops mwcc merging two adjacent outgoing stack-argument stores.
 * The 108 matched examples are the corpus to mine -- pick a few whose 5th and 6th arguments
 * are constants (if any are) and see what their sources do differently.
 */
typedef struct {
    int   f00;
    int   f04;
    char  pad08[2];
    short f0a;
    int   f0c;
    int   f10;
    int   f14;
    int   f18;
    int   f1c;
    int   f20;
    char  pad24[4];
    int   f28;
    int   f2c;
    int   f30;
    int   f34;
    int   f38;
    int   f3c;
    int   f40;
    char  pad44[8];
    unsigned char f4c;
    char  pad4d[3];
} EmitDesc;

extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void func_ov022_020911f0(void *p, int a, int b);
extern void func_ov022_02091298(void *p, char *self, void *tbl, EmitDesc *d, int n, int k);
extern char data_ov045_020b4c08[];
extern void func_ov045_020b4968(void);
extern void func_ov045_020b4900(void);

void func_ov045_020b476c(char *self) {
    EmitDesc d[2];
    void *obj;

    obj = NNSi_FndAllocFromDefaultExpHeap(0x30);
    *(void **)(self + 0x2644) = obj;
    func_ov022_020911f0(obj, 0, 2);

    d[0].f40 = 0x1333;
    d[1].f0c = 0x2000 - 0x1333;
    d[0].f14 = 0xa000;
    d[1].f14 = 0xa000;
    d[0].f18 = 0x12000;
    d[1].f18 = 0x12000;
    d[0].f30 = 0x300;
    d[1].f30 = 0x300;
    d[1].f00 = 5 + 0x3dc;
    d[0].f00 = 0x1e1;
    d[0].f0c = 0x800;
    d[1].f40 = 0x2000;
    d[1].f3c = 3;
    d[1].f38 = 0x25;
    d[0].f04 = 0;
    d[0].f0a = 0;
    d[0].f10 = 0;
    d[0].f1c = 0;
    d[0].f20 = 0;
    d[0].f28 = 0;
    d[0].f2c = 0x100;
    d[0].f34 = 0x100;
    d[0].f4c = 0xa;
    d[0].f38 = 5;
    d[0].f3c = 2;
    d[1].f04 = 0;
    d[1].f0a = 0;
    d[1].f10 = 0;
    d[1].f1c = 0;
    d[1].f20 = 0;
    d[1].f28 = 0;
    d[1].f2c = 0x100;
    d[1].f34 = 0x100;
    d[1].f4c = 0xa;

    func_ov022_02091298(*(void **)(self + 0x2644), self, data_ov045_020b4c08, d, 2, 0xa);
    *(void **)(*(char **)(self + 0x2644) + 0x20) = (void *)&func_ov045_020b4968;
    *(void **)(*(char **)(self + 0x2644) + 0x24) = (void *)&func_ov045_020b4900;
}
