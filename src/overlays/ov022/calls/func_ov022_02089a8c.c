typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Actor {
    u8 pad000[0x4d0];
    s8 nChosenKind;                  /* 0x4d0 */
    u8 pad4d1[1];
    u16 nChosenArg;                  /* 0x4d2 */
    u16 nChosenArg2;                 /* 0x4d4 */
    u8 pad4d6[0x12];
    u8 bInput0 : 1;                  /* 0x4e8 bit 0 */
    u8 bInput1 : 1;                  /*       bit 1 */
    u8 bInput2 : 1;                  /*       bit 2 */
    u8 bInput3 : 1;                  /*       bit 3 */
    u8 nInputSpare : 4;
    u8 pad4e9[0x217f];
    int nLandingPoint;               /* 0x2668 */
    u8 pad266c[0x558];
    void *pWallSurface;              /* 0x2bc4 */
};

struct SessionState {
    u8 pad00[1];
    s8 nKind;                        /* 0x01 */
};

/* What the reference query writes back: kind, id and index as loose bytes. */
struct RefOut {
    u8 nKind;                        /* 0x00 */
    u8 nId;                          /* 0x01 */
    u8 nIndex;                       /* 0x02 */
    u8 pad03[1];
};

/* The reference triple the packet carries in its third word. */
struct RefWord {
    u16 nKind : 2;                   /* bits 0-1 */
    u16 nMode : 1;                   /* bit 2 */
    u16 nIndex : 5;                  /* bits 3-7 */
    u16 nId : 8;                     /* bits 8-15 */
};

/* The 0xc-byte control packet gate 3 receives. */
struct InputPacket {
    u16 nField00;                    /* 0x00 */
    u16 nSlot : 3;                   /* 0x02 bits 0-2 */
    u16 nInput : 12;                 /*      bits 3-14 */
    u16 bInput0 : 1;                 /*      bit 15 */
    u32 nChosenKind : 4;             /* 0x04 bits 0-3 */
    u32 nChosenArg : 10;             /*      bits 4-13 */
    u32 nChosenArg2 : 10;            /*      bits 14-23 */
    u32 bInput1 : 1;                 /*      bit 24 */
    u32 bInput3 : 1;                 /*      bit 25 */
    u32 bSupported : 1;              /*      bit 26 */
    u32 nSpare : 5;
    struct RefWord ref;              /* 0x08 */
    u16 pad0a;                       /* 0x0a */
};

#define GATE_CONTROL 3
#define CHOSEN_NONE 7
#define STATE_KIND_HELD 2
#define INPUT_MASK_A 0xf0
#define INPUT_MASK_B 0xc03

extern u16 data_0204c18c;

extern void MI_CpuFill8(void *pDst, u32 nValue, u32 nSize);
extern int func_ov002_0206aaa0(void);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern int func_ov002_0204cb18(int nSession);
extern int func_01fffe14(void);
extern struct Actor *func_01fffde0(int nIndex);
extern int func_ov022_0208868c(void);
extern struct SessionState *func_ov022_02088d04(void);
extern int func_ov002_0204cb40(int nSession);
extern int func_ov002_0206b7a4(void);
extern int func_ov002_0204cecc(int nSession);
extern int func_ov022_02086654(u8 *pOut);
extern int func_ov022_02086620(int nOther);
extern int func_02031258(int nGate, u16 *pData, u16 nSize);

void func_ov022_02089a8c(void)
{
    struct InputPacket packet;
    struct RefOut refOut;
    struct Actor *pActor;
    int nSession;
    int nOther;
    int bTrimA;
    int bTrimB;
    struct SessionState *pState;
    struct RefWord *pRef;

    if (func_ov002_0206aaa0() == 0) {
        return;
    }
    nSession = func_ov022_02083f0c();
    nOther = func_ov022_02083f5c();
    if (func_ov002_0204cb18(nSession) == 0) {
        return;
    }
    MI_CpuFill8(&packet, 0, sizeof(packet));
    pActor = func_01fffde0(func_01fffe14());
    packet.nSlot = func_01fffe14();
    packet.bSupported = 0;
    if (func_ov022_0208868c() == 0) {
        bTrimA = 0;
        bTrimB = 0;
        pState = func_ov022_02088d04();
        packet.nInput = data_0204c18c;
        if (func_ov002_0204cb40(nSession) != 0) {
            bTrimA = 1;
        }
        if (pState->nKind == STATE_KIND_HELD) {
            bTrimA = 1;
        }
        if (func_ov002_0206b7a4() != 0) {
            bTrimB = 1;
        }
        if (bTrimA != 0) {
            packet.nInput &= ~INPUT_MASK_A;
        }
        if (bTrimB != 0) {
            packet.nInput &= ~INPUT_MASK_B;
        }
        packet.nChosenKind = pActor->nChosenKind;
        packet.nChosenArg = pActor->nChosenArg;
        packet.nChosenArg2 = pActor->nChosenArg2;
        packet.bInput0 = pActor->bInput0;
        packet.bInput1 = pActor->bInput1;
        packet.bInput3 = pActor->bInput3;
    } else {
        packet.nInput = 0;
        packet.nChosenKind = CHOSEN_NONE;
    }
    packet.nField00 = func_ov002_0204cecc(nSession);
    pRef = &packet.ref;
    if (pActor->nLandingPoint != 0 || pActor->pWallSurface != 0) {
        packet.bSupported = 1;
    }
    func_ov022_02086654(&refOut.nKind);
    pRef->nKind = refOut.nKind;
    pRef->nId = refOut.nId & 0xff;
    pRef->nIndex = refOut.nIndex;
    pRef->nMode = func_ov022_02086620(nOther);
    func_02031258(GATE_CONTROL, (u16 *)&packet, sizeof(packet));
    pActor->nChosenKind = CHOSEN_NONE;
    pActor->bInput1 = 0;
}
