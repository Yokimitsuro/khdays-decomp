/* ov022: keep the rumble in step with whether the local player is on flat ground.
 *
 * Only the local player's own object drives it -- anyone else's is left alone
 * and reported as flat, so a remote player never shakes the pad.
 *
 * Flat is the default. It is only given up when the actor's collision block has
 * a contact mode set and a contact array to read: the face's packed normal is
 * widened and its vertical has to come within a hair of straight up. A slope
 * shallower than that counts as not flat.
 *
 * Either way the rumble is told the answer, on with a fixed strength or off.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

#define FLAT_MIN 0xfc0
#define RUMBLE_STRENGTH 0x333

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022CollBlock */
struct CollBlock {
    int nHandle;                 /* 0x00 */
    s16 *pContacts;              /* 0x04 */
    void *pRide;                 /* 0x08 */
    u8 pad00c[0x90];
    int nContactY;               /* 0x9c */
    u8 pada0[4];
    int nContactMode;            /* 0xa4 */
};

/* Ov022Actor */
struct Actor {
    u8 pad000[8];
    u8 nOwner;                   /* 0x0008 */
    u8 pad009[0x5f];
    struct CollBlock collMain;   /* 0x0068 */
};

extern int func_02030788(void);
extern void func_02028d74(void *pModel, s16 *pFace, struct VecFx32 *pOut);
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cdf4(int nHandle, int bOn, int nStrength);

int func_ov022_020ad718(struct Actor *pActor)
{
    struct VecFx32 vecNormal;
    struct CollBlock *pColl;
    int bFlat;

    bFlat = 1;
    if (pActor->nOwner != func_02030788()) {
        return bFlat;
    }
    if (pActor->collMain.nContactMode != 0
        && (pColl = &pActor->collMain) != 0 && pColl->pContacts != 0) {
        func_02028d74((void *)pColl->nHandle, pColl->pContacts + 0xa,
                      &vecNormal);
        if (vecNormal.y <= FLAT_MIN) {
            bFlat = 0;
        }
    }
    if (bFlat != 0) {
        func_ov002_0204cdf4(func_ov022_02083f0c(), 1, RUMBLE_STRENGTH);
    } else {
        func_ov002_0204cdf4(func_ov022_02083f0c(), 0, 0);
    }
    return bFlat;
}
