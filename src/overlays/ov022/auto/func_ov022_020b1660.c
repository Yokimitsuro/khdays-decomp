/* ov022: work out which part a request id lands on.
 *
 * Most ids map straight onto a part and a few share one. Two answers depend on
 * the owner's alternate flag: id 0x1a picks part 4 instead of part 5, and in the
 * open range past 0x1b the single id 0x35 does the same. Everything else in that
 * range is a plain offset, and anything below it has no part at all.
 *
 * The flag word at 0x464 is 64 bits wide, which is why testing bit 7 of it masks
 * the low half with 0x80 and the high half with nothing at all.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Actor {
    u8 pad000[0x464];
    u32 aFlags2[2];              /* 0x464: halves of one 64-bit flag word */
};

#define ACTOR_FLAGS2(pActor) (*(unsigned long long *)(pActor)->aFlags2)

struct AnimRequest {
    void *pTrack;                /* 0x00 */
    struct Actor *pOwner;        /* 0x04 */
};

int func_ov022_020b1660(struct AnimRequest *pReq, int nWhich)
{
    struct Actor *pOwner;
    int bAlt;
    int nPart;

    pOwner = pReq->pOwner;
    bAlt = 0;
    nPart = -1;
    if ((ACTOR_FLAGS2(pOwner) & 0x80) != 0) {
        bAlt = 1;
    }
    switch (nWhich) {
    case 0x0e:
    case 0x0f:
        nPart = 1;
        break;
    case 0x11:
    case 0x12:
        nPart = 2;
        break;
    case 0x13:
    case 0x14:
        nPart = 3;
        break;
    case 0x1a:
        nPart = 5;
        if (bAlt != 0) {
            nPart = 4;
        }
        break;
    case 0x17:
        nPart = 6;
        break;
    case 0x18:
        nPart = 7;
        break;
    case 0x19:
        nPart = 8;
        break;
    default:
        if (nWhich >= 0x1b) {
            nPart = nWhich - 0x12;
            if (bAlt != 0) {
                if (nWhich - 0x1b == 0x1a) {
                    nPart = 4;
                }
            }
        }
        break;
    }
    return nPart;
}
