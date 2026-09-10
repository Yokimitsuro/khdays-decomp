/* ov022: what the actor is worth at this scale.
 *
 * The base value comes from the actor's own record plus whatever bonus it is
 * carrying, both in whole units, and is capped before the caller's scale is
 * applied. A further discount is taken when the actor has a partner slot, that
 * slot answers the partner query, and the pair are not already matched. The
 * answer is handed back in whole units again.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed long long s64;

#define VALUE_CAP 0x3e7000
#define PARTNER_QUERY 0x48
#define PARTNER_DISCOUNT 0x1333
#define NO_PARTNER (-1)

/* Per-id table of 0x104-byte records. */
struct Record {
    u8 pad0000[0xa];
    u16 nBaseValue;              /* 0x000a */
    u8 pad000c[0xf8];
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x912];
    short nBonusValue;           /* 0x091c */
    u8 pad091e[0x1976];
    int nPartnerSlot;            /* 0x2294 */
};

extern struct Record data_0204c678[];

extern int func_020358f4(int nId, int nWhat);
extern int func_020357f4(int nId, int nSlot);

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

int func_ov022_020a216c(struct Actor *pActor, int nScale, int nActionLevel)
{
    struct Record *pRec;
    int nValue;

    pRec = &data_0204c678[pActor->nId];
    nValue = 0;
    nValue += pRec->nBaseValue << 12;
    nValue += pActor->nBonusValue << 12;
    if (nValue >= VALUE_CAP) {
        nValue = VALUE_CAP;
    }
    nValue = FxMul(nValue, nScale);
    if (pActor->nPartnerSlot != NO_PARTNER
        && func_020358f4(pActor->nId, PARTNER_QUERY) != 0
        && func_020357f4(pActor->nId, pActor->nPartnerSlot) == 0) {
        nValue = FxMul(nValue, PARTNER_DISCOUNT);
    }
    return nValue >> 12;
}
