/* Reset the menu root back to state 1: re-init the sub-object at +0xdc, and if a
 * slot is still bound at +0xbc release it three ways and mark it free (-1). When
 * the secondary object at +0x04 is absent, run func_ov002_0205311c first. Always
 * reports 0.
 *
 * The bound slot is read twice rather than cached -- that is the ROM, and the
 * second read is what keeps the two release calls in the same register. */
typedef struct {
    int nState;             /* +0x00 */
    int pSecondary;         /* +0x04 */
    char pad08[0xb4];
    int nBoundSlot;         /* +0xbc, -1 = free */
    char padc0[0x1c];
    int aSubObject[1];      /* +0xdc */
} Ov002MenuRoot;

extern void func_ov002_02054430(void *sub);
extern void func_ov002_02053938(int slot);
extern void func_ov002_020539f4(int slot);
extern void func_ov002_02053d10(void);
extern void func_ov002_0205311c(void);
extern void func_ov002_02053190(void);

extern Ov002MenuRoot *data_ov002_0207f60c;

int func_ov002_02053484(void) {
    Ov002MenuRoot *ctx = data_ov002_0207f60c;

    func_ov002_02054430(ctx->aSubObject);

    if (ctx->nBoundSlot >= 0) {
        func_ov002_02053938(ctx->nBoundSlot);
        func_ov002_020539f4(ctx->nBoundSlot);
        func_ov002_02053d10();
        ctx->nBoundSlot = -1;
    }

    if (ctx->pSecondary == 0) {
        func_ov002_0205311c();
    }

    ctx->nState = 1;
    func_ov002_02053190();
    return 0;
}
