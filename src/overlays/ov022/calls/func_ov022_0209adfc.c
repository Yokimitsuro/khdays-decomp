/* ov022: start the actor's charge block.
 *
 * Clears the two running bits, marks the block with the starting knockdown kind
 * and resets the animation slot. Each of the three charge entries is then bound
 * to its own track set, and the actor is put through two states so the block is
 * live from the first frame. Finally the actor's own record supplies the
 * knockdown kind and the two meter values, which is why the starting kind above
 * only survives until here.
 */

typedef unsigned char u8;
typedef signed char s8;

#define ENTRY_STRIDE 0x108
#define ENTRY_COUNT 3
#define START_KIND 0xe

/* Ov022Charge */
struct Charge {
    s8 nKnockdownKind;           /* 0x0000 */
    u8 pad0001[3];
    int nMeter;                  /* 0x0004 */
    int nField0008;              /* 0x0008, the record's other meter value */
    u8 bReleased;                /* 0x000c, bits 0 and 1 are the running pair */
    u8 pad000d[0xf];
    u8 aEntries[ENTRY_COUNT][ENTRY_STRIDE];   /* 0x001c */
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x2766];
    struct Charge charge;        /* 0x2770 */
};

/* Per-id table of 0x44-byte records; the knockdown kind and the two meter
 * values live here. */
struct Record {
    u8 pad0000[0x26];
    s8 nKnockdownKind;           /* 0x0026 */
    u8 pad0027;
    int nField0028;              /* 0x0028 */
    int nMeter;                  /* 0x002c */
    u8 pad0030[0x14];
};

extern struct Record data_0204c3d8[];

/* Three track sets, one per charge entry. */
struct EntryNames {
    u8 *ap[ENTRY_COUNT];
};

extern struct EntryNames data_ov022_020b25a8;

extern void func_ov022_0209b1e8(struct Actor *pActor);   /* reset the animation slot */
extern void func_0202a634(u8 *pEntry, u8 *pTracks, int nA, int nB);
extern void func_ov022_0209b078(struct Actor *pActor, int nState,
                                int nArg);              /* enter a state */

void func_ov022_0209adfc(struct Actor *pActor)
{
    struct EntryNames names;
    struct Charge *pCharge;
    struct Record *pRec;
    int nEntry;

    pCharge = &pActor->charge;
    pCharge->bReleased &= ~1;
    pCharge->bReleased &= ~2;
    pActor->charge.nKnockdownKind = START_KIND;
    func_ov022_0209b1e8(pActor);
    names = data_ov022_020b25a8;
    for (nEntry = 0; nEntry < ENTRY_COUNT; nEntry++) {
        func_0202a634(pCharge->aEntries[nEntry], names.ap[nEntry], 1, 5);
    }
    func_ov022_0209b078(pActor, 2, 0);
    func_ov022_0209b078(pActor, 0, 0);
    pRec = &data_0204c3d8[pActor->nId];
    pCharge->nKnockdownKind = pRec->nKnockdownKind;
    pCharge->nField0008 = pRec->nField0028;
    pCharge->nMeter = pRec->nMeter;
}
