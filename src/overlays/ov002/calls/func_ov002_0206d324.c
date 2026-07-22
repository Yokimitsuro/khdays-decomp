/* Has the session block reached at least phase 2, and if it is sitting exactly
 * at 2, advance it to 3. Reports whether the caller may proceed.
 *
 * The phase word is reached as (block at +0x8bcc)->phase at +0xc0 rather than as
 * one flat +0x8c8c offset: the ROM rebuilds the address from the block base for
 * the store instead of reusing the one it already had, which is what a second
 * field expression on the same sub-object looks like. */
typedef struct {
    char pad0000[0xc0];
    int nPhase;             /* +0xc0 */
} Ov002SessionBlock;

typedef struct {
    char pad0000[0x8bcc];
    Ov002SessionBlock session;  /* +0x8bcc */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

int func_ov002_0206d324(void) {
    Ov002SessionBlock *block = &data_ov002_0207fa00->session;

    if (block->nPhase < 2) {
        return 0;
    }

    if (block->nPhase == 2) {
        block->nPhase = 3;
    }

    return 1;
}
