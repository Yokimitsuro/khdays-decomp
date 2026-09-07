/* ov022: fire the charge release once the meter is full.
 *
 * Nothing happens unless a request is pending, that request is the one kind
 * this path handles, and the meter has reached its threshold. When all three
 * hold, a request is built on the stack from a fixed id and a fixed offset and
 * handed to the spawner, the slot is marked active, and the follow-up runs.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define RELEASE_ID 0xe4a
#define RELEASE_KIND 0xb
#define CHARGE_FULL 0xa000

struct Vec3 {
    int x, y, z;
};

struct Actor;

struct Request {
    int nId;                     /* 0x00 */
    struct Vec3 vecOffset;       /* 0x04 */
    int nSpare;                  /* 0x10 */
    int nKind;                   /* 0x14 */
    u8 bFlag;                    /* 0x18 */
    u8 pad19[3];
    struct Actor *pOwner;        /* 0x1c */
    u8 pad20[8];
};

struct Charge {
    signed char nKnockdownKind;  /* 0x00 */
    u8 pad01[3];
    int nMeter;                  /* 0x04 */
    u8 pad08[4];
    u8 bReleased : 1;            /* 0x0c */
};

struct Actor {
    u8 pad0000[0x2770];
    struct Charge charge;        /* 0x2770 */
};

extern const struct Vec3 data_02041dc8;
extern void func_ov022_020a08a8(struct Actor *pActor, struct Request *pReq,
                                int nKind);
extern void func_ov022_0209b1e8(struct Actor *pActor);

void func_ov022_0209bd10(struct Actor *pActor)
{
    struct Request req;
    struct Charge *pCharge;

    pCharge = &pActor->charge;

    if (pCharge->nKnockdownKind == -1) {
        return;
    }
    if (pCharge->nKnockdownKind != RELEASE_KIND) {
        return;
    }
    if (pCharge->nMeter < CHARGE_FULL) {
        return;
    }
    req.vecOffset = data_02041dc8;
    req.nSpare = 0;
    req.nId = RELEASE_ID;
    req.nKind = RELEASE_KIND;
    req.bFlag = 0;
    req.pOwner = pActor;
    func_ov022_020a08a8(pActor, &req, RELEASE_KIND);
    pCharge->bReleased = 1;
    func_ov022_0209b1e8(pActor);
}
