/* Drop the actor into state 0xe: if it was in state 0xc, tell func_ov002_0206df6c first;
 * then reset the state block at +0x2770 (both state bytes, the three counters, and bit 1 of
 * the flag byte), mirror the state into +0x2ab8, and run the follow-up.
 *
 * Two things the park had wrong, neither of them a codegen tie:
 *   - func_ov002_0206df6c takes TWO arguments. The original sets only r0 and r1 and stores
 *     nothing to the stack, so the "5th argument in the pushed-r3 slot" the note described
 *     does not exist. `push {r3,...}` is alignment padding.
 *   - `&= 0xfd` compiles to `and`; the original has `bic`, which is what `&= ~2` gives.
 * The two spellings of the same address are real, though: the state read splits 0x2770 as
 * 0x2700+0x70 because it is written inline, while the block pointer splits it as 0x770+0x2000.
 * Keeping them as separate expressions is what reproduces both splits. */
extern void func_ov002_0206df6c(int actor, int mode);
extern void func_ov022_0209be44(int self);

struct Ov022StateBlk {
    signed char bState;         /* +0x00 */
    unsigned char bStateEcho;   /* +0x01 */
    char _pad02[2];
    int nTimerA;                /* +0x04 */
    int nTimerB;                /* +0x08 */
    unsigned char bFlags;       /* +0x0c */
    char _pad0d[3];
    int nTimerC;                /* +0x10 */
};

void func_ov022_0209b1e8(int self) {
    struct Ov022StateBlk *blk = (struct Ov022StateBlk *)(self + 0x2770);
    if (*(signed char *)(self + 0x2770) == 0xc) {
        func_ov002_0206df6c(*(unsigned char *)(self + 9), 0);
    }
    blk->bState = 0xe;
    blk->bStateEcho = 0xe;
    blk->nTimerA = 0;
    blk->nTimerB = 0;
    blk->nTimerC = 0;
    blk->bFlags &= ~2;
    *(unsigned char *)(self + 0x2ab8) = 0xe;
    func_ov022_0209be44(self);
}
