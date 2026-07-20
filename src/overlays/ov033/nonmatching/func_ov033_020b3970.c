/* func_ov033_020b3970 -- message handler: 0x21 arms the intro state, 0x22 re-aims at the
 * tracked target, 0x23 hands over to the outro.
 *
 * NONMATCHING: 324/332, EIGHT bytes short, and both missing instructions are in one block.
 *
 * SEMANTICS: returns the handler to install next, or null for any other message.
 *   0x21: if the global check clears, set bit 16 of the flag word at +0x464 and touch the
 *         one at self+0x64's +0x404; then report 0x33 or 0x2f to the owner depending on
 *         whether the sub-object at self+0x22f8 is active.
 *   0x22: notify, latch 1 into the block at +0x2c2c+8, report 0x31 or 0x30 on the same
 *         test, and if the angle at self+0x2abc is not -1, add the offset at self+0x478 to
 *         it and write the result plus half a turn into the node's angle with the dirty bit.
 *   0x23: report 0x32.
 *
 * THE MISSING BLOCK, exactly:
 *      ROM   add r0,r5,#0x64 ; ldr r2,[r5,#0x464] ; ldr r1,[r0,#0x404]
 *            orr r2,r2,#0x10000 ; str r2,[r5,#0x464] ; orr r1,r1,#0 ; str r1,[r0,#0x404]
 *      ours  ldr r0,[r5,#0x464] ; ldr r1,[r5,#0x468]
 *            orr r0,r0,#0x10000 ; str r0,[r5,#0x464] ; str r1,[r5,#0x468]
 * Two things are absent: the SEPARATE BASE at self+0x64 (we fold 0x64+0x404 into the single
 * encodable offset 0x468, which the ROM does not) and the `orr r1, r1, #0`.
 *
 * ** CORRECTION to what I wrote on func_ov046_020b362c the same day. **  I claimed there
 * that `*(volatile int *)p |= 0` "keeps the read-modify-write and emits the instruction".
 * It does not.  Volatile brings back the LOAD and the STORE -- worth 4 bytes per site, and
 * that is the +16 measured on ov046's two sites -- but mwcc still folds the `| 0` away, so
 * the `orr` is missing in both functions.  ov046's remaining 20-byte gap and this one's 8
 * are the same two unknowns.  Measured here across five spellings: plain `|= 0`, volatile
 * `|= 0`, an explicit `*p = *p | 0`, the same through a volatile pointer local, and with
 * the value read into a plain int first -- all 324, none emits the orr.  A `char *volatile`
 * base overshoots to 348.
 *
 * So the open question for BOTH functions is a single one: what source construct makes mwcc
 * emit an OR with an immediate zero, and does it also force the two-step base?  The fact
 * that the ROM pairs them -- base register plus no-op OR, twice in ov046 and once here --
 * suggests one construct produces both, most likely a macro or inline helper taking a base
 * pointer and a mask that happens to be zero at these call sites.
 */
extern int func_02030788(void);
extern void func_ov022_020a2954(char *self);
extern int func_ov022_02095554(char *p);
extern void func_ov033_020b3bc4(void);
extern void func_ov033_020b3e10(void);
extern void func_ov033_020b4038(void);

void *func_ov033_020b3970(char *self, int msg) {
    char *blk = self + 0x2c + 0x2c00;
    void *next = 0;
    int *node;
    int base;

    switch (msg) {
    case 0x21:
        if (func_02030788() == 0) {
            *(int *)(self + 0x464) |= 0x10000;
            *(volatile int *)(self + 0x64 + 0x404) =
                *(volatile int *)(self + 0x64 + 0x404) | 0;
        }
        next = (void *)&func_ov033_020b3bc4;
        if (func_ov022_02095554(self + 0x2f8 + 0x2000) != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x33);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        }
        break;
    case 0x22:
        func_ov022_020a2954(self);
        next = (void *)&func_ov033_020b3e10;
        if (func_ov022_02095554(self + 0x2f8 + 0x2000) != 0) {
            *(int *)(blk + 8) = 1;
            (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        } else {
            *(int *)(blk + 8) = 1;
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        }
        base = *(int *)(self + 0x2000 + 0xabc);
        if (base != -1) {
            node = *(int **)(self + 0x20);
            if ((node[0] & 0x20) == 0) {
                *(unsigned short *)((char *)node + 0x80) =
                    (unsigned short)(base + *(short *)(self + 0x400 + 0x78)) + 0x8000;
                *(unsigned short *)((char *)node + 4) |= 0x20;
            }
        }
        break;
    case 0x23:
        next = (void *)&func_ov033_020b4038;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        break;
    }
    return next;
}
