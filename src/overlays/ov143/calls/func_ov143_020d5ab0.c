/* The slam's follow-through (Ghidra: Ov143_StepSlamStrike).
 *
 * Every frame it re-aims the sub-object at its stored facing and rescales the
 * velocity, then builds the query the two search modes share: the anchor
 * position, the facing, the speed and a fixed 0x800 range.
 *
 * Mode 0 sweeps the actor list and asks the shared checker whether each
 * candidate is hit; the first acceptance ends the action. Mode 1 instead locks
 * on, fills a request with the owner's id, the object's kind and the lock
 * handle, and ends the action if the lock is taken. Either way the ending
 * broadcasts a type 5 action 0 placement command and fires reaction 0x53.
 *
 * With neither search producing anything the timer advances by the speed, and
 * the action still ends -- with a type 5 action 1 command and no sound -- once
 * the object reports contact or the timer passes 0xa000.
 *
 * Three codegen notes, because the frame layout is what this function is really
 * about.
 *
 * Each anchor component is written to a scratch word nothing ever reads before
 * it is packed, one word at a time through a one-word struct. That is what
 * keeps the store alive through dead-store elimination so it fuses with the
 * packing.
 *
 * Those nine scratch words are nine separate scalars, not three vectors. The
 * compiler sinks an address-taken SCALAR to the bottom of the frame but leaves
 * an address-taken aggregate where its declaration puts it, so spelling them as
 * three twelve-byte vectors parks them above the two requests instead of below
 * them, and every slot in the function shifts by the 0x24 bytes they occupy.
 *
 * Within one group the slots are handed out in reverse declaration order, which
 * is why the three components of each site are declared z, y, x, and why the
 * loop bound is declared after the loop counter.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 { int x, y, z; };
struct Word { int w; };
struct Ov143Cmd { u16 h[7]; };
struct Ov143Quat { int q[4]; };

struct Ov143Query {
    struct Vec3 vAnchor;
    struct Vec3 vFacing;
    int nSpeed;
    int nRange;
};

/* The same 44-byte command the four sibling overlays build for this entry
   point, kept field-for-field identical to them. */
struct HitCommand {
    u32 flags00;
    struct Vec3 vector04;
    u32 field10;
    u32 field14;
    void *hit18;
    int pad1c[4];
};

struct Ov143Contact { u8 bGrounded : 1, bBlocked : 1; };

struct Ov143Owner {
    char pad000[0x290];
    u16 nId290;
};

struct Ov143SubObj {
    char pad000[0x24];
    void (*pMsgHook24)(struct Ov143SubObj *self, void *msg, int len); /* 0x024 */
    char pad028[0x78];
    char aSrtA0[0x2c];                                             /* 0x0a0 */
    char pad0cc[0xae];
    u8 bContact17a;                                                /* 0x17a */
    char pad17b[0x4c];
    u8 bSubState1c7;                                               /* 0x1c7 */
    char pad1c8[0x90];
    int nKind258;                                                  /* 0x258 */
    int nLockParam25c;                                             /* 0x25c */
    char pad260[0x138];
    struct Ov143Owner *pOwner398;                                  /* 0x398 */
};

struct Ov143StepState {
    struct Ov143SubObj *pSelf;   /* 0x00 */
    struct Vec3 *pAnchor;        /* 0x04 */
    struct Vec3 vVelocity08;     /* 0x08 */
    struct Vec3 vFacing14;       /* 0x14 */
    int nMode20;                 /* 0x20 */
    int nTimer24;                /* 0x24 */
    int nSpeed28;                /* 0x28 */
};

struct Ov143StepNode {
    void *pClock;                  /* 0x00 */
    struct Ov143StepState *pState; /* 0x04 */
    char pad08[0x18];
    signed char bSlot;             /* 0x20 */
};

extern struct Vec3 data_02042258;
extern struct Vec3 data_02041dc8;
extern struct Ov143Cmd data_ov143_020d6270;
extern struct Ov143Cmd data_ov143_020d628c;
extern struct Ov143Cmd data_ov143_020d629a;

extern void func_0202ed60(struct Ov143Quat *out, const struct Vec3 *from,
                          const struct Vec3 *to);
extern void func_0203c9d0(void *srt, const struct Ov143Quat *rot);
extern void func_01ffa724(int scale, const struct Vec3 *src, struct Vec3 *dst);
extern int func_ov107_020c8f44(struct Ov143Owner *owner, struct Ov143Query *query,
                               int *results);
extern int func_ov107_020ca918(int ent, struct Ov143SubObj *self,
                               struct Ov143Owner *owner, int mode, void *dir,
                               int flag);
extern void *func_ov107_020c9184(struct Ov143SubObj *self, struct Ov143Query *query,
                                 void **out);
extern int func_ov107_020c5cfc(void *lock, int param, struct HitCommand *req);
extern void func_ov107_020c5af8(struct Ov143Owner *owner, int a, int id, void *at);
extern void func_0203c634(struct Ov143StepNode *node, int slot, void *value);

#define PACK(cmd, dead, s, i, at)                                             \
    *(struct Word *)&(dead) = (s)[i];                                         \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead) >> 0x10 & 0x7f)           \
                              | ((unsigned int)(dead) >> 0x18 & 0x80));       \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead) >> 8);               \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead)

void func_ov143_020d5ab0(struct Ov143StepNode *node)
{
    struct Ov143StepState *state = node->pState;
    struct Ov143Query query;
    struct Ov143Quat rot;
    int results[4];
    struct Ov143Cmd cmdHit;
    void *handle;
    int hitScratchZ;
    int hitScratchY;
    int hitScratchX;
    int lockScratchZ;
    int lockScratchY;
    int lockScratchX;
    int endScratchZ;
    int endScratchY;
    int endScratchX;
    struct Word *s;
    void *lock;
    int i;
    int n;

    func_0202ed60(&rot, &data_02042258, &state->vFacing14);
    func_0203c9d0(state->pSelf->aSrtA0, &rot);
    func_01ffa724(state->nSpeed28, &state->vFacing14, &state->vVelocity08);

    query.vAnchor = *state->pAnchor;
    query.vFacing = state->vFacing14;
    query.nSpeed = state->nSpeed28;
    query.nRange = 0x800;

    if (state->nMode20 == 0) {
        n = func_ov107_020c8f44(state->pSelf->pOwner398, &query, results);
        i = 0;
        if (n > 0) {
            do {
                if (func_ov107_020ca918(results[i], state->pSelf,
                                        state->pSelf->pOwner398, 0,
                                        &state->vVelocity08, 0) != 0) {
                    cmdHit = data_ov143_020d6270;
                    s = (struct Word *)state->pAnchor;
                    PACK(cmdHit, hitScratchX, s, 0, 5);
                    PACK(cmdHit, hitScratchY, s, 1, 8);
                    PACK(cmdHit, hitScratchZ, s, 2, 11);
                    if (state->pSelf->pMsgHook24 != 0) {
                        state->pSelf->pMsgHook24(state->pSelf, &cmdHit, 0xe);
                    }
                    func_ov107_020c5af8(state->pSelf->pOwner398, 0, 0x53,
                                        state->pAnchor);
                    state->pSelf->bSubState1c7 = 0;
                    func_0203c634(node, node->bSlot, 0);
                    return;
                }
            } while (++i < n);
        }
    } else {
        struct HitCommand spare = { 0 };

        if ((lock = func_ov107_020c9184(state->pSelf, &query, &handle)) != 0) {
            struct HitCommand req = { 0 };

            req.flags00 = (req.flags00 & 0xffff0000) | 0x2004;
            req.vector04 = data_02041dc8;
            req.field10 = (req.field10 & 0xffff0000)
                  | (u16)state->pSelf->pOwner398->nId290;
            req.field14 = (req.field14 & 0xffff0000)
                  | (u16)state->pSelf->nKind258;
            req.hit18 = handle;
            if (func_ov107_020c5cfc(lock, state->pSelf->nLockParam25c, &req) != 0) {
                struct Ov143Cmd cmdLock;

                cmdLock = data_ov143_020d628c;
                s = (struct Word *)state->pAnchor;
                PACK(cmdLock, lockScratchX, s, 0, 5);
                PACK(cmdLock, lockScratchY, s, 1, 8);
                PACK(cmdLock, lockScratchZ, s, 2, 11);
                if (state->pSelf->pMsgHook24 != 0) {
                    state->pSelf->pMsgHook24(state->pSelf, &cmdLock, 0xe);
                }
                func_ov107_020c5af8(state->pSelf->pOwner398, 0, 0x53,
                                    state->pAnchor);
                state->pSelf->bSubState1c7 = 0;
                func_0203c634(node, node->bSlot, 0);
                return;
            }
        }
    }

    state->nTimer24 += state->nSpeed28;
    if (((struct Ov143Contact *)&state->pSelf->bContact17a)->bGrounded == 0
        && ((struct Ov143Contact *)&state->pSelf->bContact17a)->bBlocked == 0
        && state->nTimer24 <= 0xa000) {
        return;
    }

    {
    struct Ov143Cmd cmdEnd;

    cmdEnd = data_ov143_020d629a;
    s = (struct Word *)state->pAnchor;
    PACK(cmdEnd, endScratchX, s, 0, 5);
    PACK(cmdEnd, endScratchY, s, 1, 8);
    PACK(cmdEnd, endScratchZ, s, 2, 11);
    if (state->pSelf->pMsgHook24 != 0) {
        state->pSelf->pMsgHook24(state->pSelf, &cmdEnd, 0xe);
    }
    state->pSelf->bSubState1c7 = 0;
    func_0203c634(node, node->bSlot, 0);
    }
}
