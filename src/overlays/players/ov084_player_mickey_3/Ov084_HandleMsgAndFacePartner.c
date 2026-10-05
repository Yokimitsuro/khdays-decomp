/* Message handler: arm the follow-up state for messages 0x21 and 0x22, and on 0x22 also
 * turn the actor to face its partner.
 *
 * Returns the handler to install next, or null for any other message.  On 0x22 it clears
 * the pending field, maps the mode at +0x110 (2, 3, 4) onto 0, 1, 2 at +0x124, tells the
 * owner 0x31 or 0x30 depending on whether that mode reached 4, and then -- if the partner
 * lookup succeeds -- takes the vector from the partner to the actor's own anchor at +0x48c,
 * normalises it when non-degenerate, and writes the reversed bearing plus half a turn into
 * the node's angle field, setting the dirty bit.  A node already carrying flag 0x20 is left
 * alone.
 *
 * TWO LEVERS, and both are in the catalogue but easy to miss together:
 *  - the two dispatches must be SWITCH statements, not if-chains.  The ROM jumps TO each
 *    case (`cmp ; beq <block>` and a trailing `b default`), while an if-chain falls INTO
 *    the next test and lets mwcc predicate the small bodies (`streq`, `moveq`).  Same
 *    semantics, 8 bytes apart, and it applies to the inner 2/3/4 selection as well as the
 *    outer message test.
 *  - func_ov022_020ad0c0's RETURN VALUE is VEC_Subtract's first argument.  Written as a
 *    statement followed by a subtraction from a fixed address it is 12 bytes short: the
 *    ROM leaves r0 alone across the call boundary precisely because it is being consumed.
 *    Checklist item 5, and the tell is a `bl` with no visible use of its result.
 */

#include "nitro/fx_types.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int VEC_Mag(const VecFx32 *v);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *unit);
extern int FX_Atan2Idx(int x, int z);
extern int Ov022_ValidateTargetRef(char *self);
extern VecFx32 *func_ov022_020ad0c0(char *self);
extern char *data_ov084_020b9a20;
extern void Ov084_StepAttackEnd(void);
extern void Ov084_LandingStep(void);

void *Ov084_HandleMsgAndFacePartner(char *self, int msg) {
    char *blk = data_ov084_020b9a20 + 0x2c80;
    void *next = 0;
    VecFx32 d;
    unsigned short a;
    int *node;

    switch (msg) {
    case 0x21:
        next = (void *)&Ov084_StepAttackEnd;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        break;
    case 0x22:
        *(int *)(blk + 0x118) = 0;
        next = (void *)&Ov084_LandingStep;
        switch (*(int *)(blk + 0x110)) {
        case 2: *(int *)(blk + 0x124) = 0; break;
        case 3: *(int *)(blk + 0x124) = 1; break;
        case 4: *(int *)(blk + 0x124) = 2; break;
        }
        if (*(int *)(blk + 0x110) >= 4) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        }
        if (Ov022_ValidateTargetRef(self) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(self), (const VecFx32 *)(self + 0x48c), &d);
            if (VEC_Mag(&d) != 0) {
                VEC_Normalize(&d, &d);
            }
            a = (unsigned short)FX_Atan2Idx(-d.x, -d.z);
            node = *(int **)(self + 0x20);
            if ((node[0] & 0x20) == 0) {
                *(unsigned short *)((char *)node + 0x80) = a + 0x8000;
                *(unsigned short *)((char *)node + 4) |= 0x20;
            }
        }
        break;
    }
    return next;
}
