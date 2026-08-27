/*
 * Arms or clears the session's leave request and reports whether the request
 * stands.
 *
 * Clearing always succeeds. Arming is unconditional for a peer, but the
 * machine that owns the session has to earn it: the bit must not already be
 * set, the alternate root field must be clear, and the slot-request gate has
 * to agree. Any of those refuses and the bit is left alone.
 *
 * One thing here is load-bearing rather than style. The already-set test is
 * its own statement while the last two checks are one condition joined by an
 * or, which is what gives the first its predicated exit and the other two a
 * shared one, exactly as the original splits them.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov002RootContext {
    char pad0000[0x8b64];
    int nFlags;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

extern int func_02030788(void);
extern int func_ov002_0206b828(void);
extern int func_ov002_02069554(void);

int func_ov002_0206b88c(int bArm)
{
    Ov002RootContext *pCtx;

    pCtx = data_ov002_0207fa00;
    if (bArm == 0) {
        pCtx->nFlags &= ~0x200;
    } else {
        if (func_02030788() == 0) {
            if ((pCtx->nFlags & 0x200) != 0) {
                return 0;
            }
            if (func_ov002_0206b828() != 0 || func_ov002_02069554() == 0) {
                return 0;
            }
        }
        pCtx->nFlags |= 0x200;
    }
    return 1;
}
