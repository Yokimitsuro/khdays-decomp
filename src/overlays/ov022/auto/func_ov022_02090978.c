/* ov022: decide which mode a slot's parts move in, from the slot's own state.
 *
 * Nine of the fifteen states answer the same fixed mode: those slots hold their
 * parts still, and the step that reads this skips aiming and moving entirely.
 *
 * The other six ask the actor. They start from the base mode and step up one:
 * three bits of the actor's second flag word each force the step on their own,
 * and failing all three, a fourth bit of that word has to be set and a bit of
 * the first word owned. Otherwise the base mode stands.
 *
 * Both flag words are sixty-four bits wide, which is why each test reads two
 * words and masks the half its constant does not reach -- the bit of the first
 * word sits above bit thirty-two, the three forcing bits of the second below
 * it.
 *
 * A state outside the table answers -1.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define MODE_UNKNOWN (-1)
#define MODE_WALK 0x17
#define MODE_STILL 0x19

/* the three that force the step on their own, then the gate and the bit of the
 * first word that gate needs */
#define FLAGS2_BIT2 0x4
#define FLAGS2_BIT6 0x40
#define FLAGS2_BIT10 0x400
#define FLAGS2_BIT7 0x80
#define FLAGS_BIT36 0x1000000000ULL

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad008[0x45c];
    u64 nFlags2;                 /* 0x0464 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0x58];
    struct Actor *pActor;        /* 0x58 */
};

int func_ov022_02090978(struct ReactionCtx *pCtx, int nSlotState)
{
    struct Actor *pActor;
    u64 nFlags2;
    int nMode;

    nMode = MODE_UNKNOWN;
    switch (nSlotState) {
    case 2:
    case 5:
    case 6:
    case 7:
    case 8:
    case 11:
    case 12:
    case 13:
    case 14:
        nMode = MODE_STILL;
        break;
    case 0:
    case 1:
    case 3:
    case 4:
    case 9:
    case 10:
        pActor = pCtx->pActor;
        nMode = MODE_WALK;
        nFlags2 = pActor->nFlags2;
        if ((nFlags2 & FLAGS2_BIT2) == 0 && (nFlags2 & FLAGS2_BIT6) == 0
            && (nFlags2 & FLAGS2_BIT10) == 0) {
            if ((nFlags2 & FLAGS2_BIT7) == 0) {
                break;
            }
            if ((pActor->nFlags & FLAGS_BIT36) == 0) {
                break;
            }
        }
        nMode = nMode + 1;
        break;
    }
    return nMode;
}
