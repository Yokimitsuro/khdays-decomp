/* Ov022_StepStaggerState -- run one frame of the stagger state and decide
 * whether it is over.
 *
 * The interrupt charge is set to half a unit. The local player raises flag-3
 * bit 7 (with flag bit 36 and flag-2 bit 7), flag-2 bit 16 and flag-3 bit 16,
 * and flag-3 bit 48 once the state has run 0x9 units. The state lasts 0xf
 * units in a live session and 0x1b otherwise; past that the run block is
 * marked, the charge raised to 0x9 units and the state ends: some models go
 * straight to state 0x18 (others only with button-2 bit 0), the rest into
 * state 2, or 0 with input bit 2 held. Without input bit 2 flag bit 46 goes
 * up and the recoil is cleared. The state's own step runs last.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Actor;

typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[4];
    int nModelId;                /* 0x000c */
    u8 pad0010[0xa];
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[8];
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[0x40];
    int nInterruptCharge;        /* 0x04b4 */
    u8 pad04b8[0x14];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x198];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x1c8c];
    u8 run[0x34c];               /* 0x22f8 */
};

#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT46 (1ULL << 46)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT16 (1ULL << 16)
#define FLAG3_BIT7 (1ULL << 7)
#define FLAG3_BIT16 (1ULL << 16)
#define FLAG3_BIT48 (1ULL << 48)
#define INPUT_BIT2 0x4
#define BUTTON2_BIT0 0x1
#define CHARGE_HALF 0x2000
#define CHARGE_STAGGER 0x9000
#define TIME_MARK 0x9000
#define TIME_END_LIVE 0xf000
#define TIME_END_SOLO 0x1b000
#define STATE_IDLE 0
#define STATE_END 2
#define STATE_STAGGER_END 0x18

extern int func_02030788(void);
extern int func_02030670(void);
extern void func_ov022_020954f8(u8 *pRun);
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);             /* Ov022_ActorSetState */

int func_ov022_020a70cc(struct Actor *pActor)
{
    int nRet;
    int nLimit;

    pActor->nInterruptCharge = CHARGE_HALF;
    nRet = 0;
    if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0
        && func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT7;
    }
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT16;
    }
    if (func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT16;
    }
    nLimit = func_02030670() != 0 ? TIME_END_LIVE : TIME_END_SOLO;
    if ((int)pActor->nStateTimer >= TIME_MARK && func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT48;
    }
    if ((int)pActor->nStateTimer >= nLimit) {
        func_ov022_020954f8(pActor->run);
        pActor->nInterruptCharge = CHARGE_STAGGER;
        switch (pActor->nModelId) {
        case 3:
        case 4:
        case 0xd:
        case 0xf:
        case 0x13:
            nRet = func_ov022_020a35f4(pActor, STATE_STAGGER_END);
            break;
        case 8:
        case 0x10:
        case 0x12:
            if ((pActor->nButtons2 & BUTTON2_BIT0) != 0) {
                nRet = func_ov022_020a35f4(pActor, STATE_STAGGER_END);
            }
            break;
        }
        if (nRet == 0) {
            if ((pActor->nInputMask & INPUT_BIT2) == 0) {
                nRet = func_ov022_020a35f4(pActor, STATE_END);
            } else {
                nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
            }
        }
    }
    if ((pActor->nInputMask & INPUT_BIT2) == 0) {
        pActor->nFlags |= FLAG_BIT46;
        pActor->nRecoil = 0;
    }
    pActor->pfnPostDraw(pActor);
    return nRet;
}
