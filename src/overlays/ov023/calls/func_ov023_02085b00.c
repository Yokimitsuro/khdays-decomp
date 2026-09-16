/* func_ov023_02085b00 -- Ov023_CmdSetupPartyActors: script command that brings the four party
 * members' actors into the event.  First the four member text files ("ba/ch/%s/w_.p2" with
 * the member's name from data_02042a70 by kind -- an empty seat or kind 0xe counts as 0) are
 * opened (02024ee8 heap 6).  Then per seat 0..3: the actor gets a walk motion (0202b850 with
 * {1, 0xccd, 0x99a}), its kind's resource table (data_ov023_0208a334; 0202b914 1 / 6), is
 * hidden (0202beb8 0) and has its member block built (ov002 020522c8 from the seat's record in
 * data_0204c678, the first record for an empty seat); its text container is bound to actor
 * seat + 4 (0202b914 1 / 0xd with the packed descriptor, whose flags come from the block's
 * first byte in a host session) and, for kinds 1 / 2 / 7, to seat + 8 as well, for kinds 9 /
 * 0x13 to seat + 8 with the flags raised by 0x50; the container is closed (02024fd4).  Finally
 * the local player's kind picks game field 0x2485 (2 bits: 0 for kinds 0x10 / 0x11, 1, 2 or 3
 * by group) and field 0x2487 (5 bits) takes the kind itself.  Returns 1. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov023SessionSlot {
    int  nField00;            /* 0x00 */
    int  nMemberKind;         /* 0x04 */
} Ov023SessionSlot;

typedef struct Ov023MemberRecord {
    u8   pad_000[4];
    u8   nByte04;             /* 0x04 */
    u8   pad_005[0x104 - 5];
} Ov023MemberRecord;          /* 0x104 */

typedef struct Ov023MotionParam {
    int  nMode;               /* 0x00 */
    int  nArg1;               /* 0x04 */
    int  nArg0;               /* 0x08 */
    int  nPad1;               /* 0x0c */
    int  nPad2;               /* 0x10 */
} Ov023MotionParam;

extern Ov023SessionSlot *func_020315c0(int nSlot);                  /* Session_GetSlotIfOccupied */
extern void  OS_SPrintf(char *pBuffer, const char *pFormat, ...);
extern void *func_02024ee8(const char *pszName, int nHeap);         /* open a text container */
extern void  func_0202b850(u16 nEntity, int nA, int nB, Ov023MotionParam *pParam, int nC); /* Entity_StartMotion */
extern void  func_0202b914(u16 nEntity, void *pTable, int nA, int nB); /* Entity_BindResource */
extern void  func_0202beb8(u16 nEntity, int bVisible);              /* Entity_SetVisible */
extern void  func_ov002_020522c8(u8 *pBlock, int nKind, int nArg);  /* build a member block */
extern void  func_02024fd4(void *pContainer);                       /* close a text container */
extern int   func_02030788(void);                                   /* Session_GetLocalPlayerIndex */
extern void  func_020235e8(int nField, int nBits, int nValue);      /* GameState_SetField */
extern const char *data_02042a70[];                                 /* member names by kind */
extern char  data_ov023_0208a5e4[];                                 /* "ba/ch/%s/w_.p2" */
extern Ov023MemberRecord data_0204c678[];                           /* the party records */
extern void *data_ov023_0208a334[];                                 /* resource tables by kind */
extern u8    data_0204c240;                                         /* session bits */

int func_ov023_02085b00(void)
{
    char szPath[0x80];
    void *apText[4];
    Ov023MotionParam param;
    u8   aBlock[0x20];
    Ov023MemberRecord *pRecord;
    int  i;
    int  nKind;
    Ov023SessionSlot *pSlot;
    u32  nFlags;

    for (i = 0; i < 4; i++) {
        pSlot = func_020315c0(i);
        if (pSlot == 0) {
            nKind = 0;
        } else {
            nKind = pSlot->nMemberKind;
        }
        if (nKind == 0xe) {
            nKind = 0;
        }
        OS_SPrintf(szPath, data_ov023_0208a5e4, data_02042a70[nKind]);
        apText[i] = func_02024ee8(szPath, 6);
    }
    pRecord = data_0204c678;
    for (i = 0; i < 4; i++) {
        Ov023MemberRecord *pUsed;

        pSlot = func_020315c0(i);
        if (pSlot == 0) {
            nKind = 0;
            pUsed = data_0204c678;
        } else {
            nKind = pSlot->nMemberKind;
            pUsed = pRecord;
        }
        param.nMode = 1;
        param.nArg0 = 0x99a;
        param.nArg1 = 0xccd;
        func_0202b850((u16)i, 0, 0, &param, 0);
        func_0202b914((u16)i, data_ov023_0208a334[nKind], 1, 6);
        func_0202beb8((u16)i, 0);
        func_ov002_020522c8(aBlock, nKind, pUsed->nByte04);
        if (data_0204c240 & 4) {
            nFlags = aBlock[0];
        } else {
            nFlags = 0;
        }
        func_0202b914((u16)(i + 4), (void *)(((((u32)apText[i] + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (nFlags & 0x1ff)), 1, 0xd);
        switch (nKind) {
        case 1:
        case 2:
        case 7:
            func_0202b914((u16)(i + 8), (void *)(((((u32)apText[i] + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (nFlags & 0x1ff)), 1, 0xd);
            break;
        case 9:
        case 0x13:
            func_0202b914((u16)(i + 8), (void *)(((((u32)apText[i] + 0x8000) & 0xfffffc) << 7) | 0x80000000 | ((nFlags + 0x50) & 0x1ff)), 1, 0xd);
            break;
        }
        func_02024fd4(apText[i]);
        pRecord++;
    }
    nKind = func_020315c0(func_02030788())->nMemberKind;
    switch (nKind) {
    case 0x10:
    case 0x11:
        func_020235e8(0x2485, 2, 0);
        break;
    case 0:
    case 5:
    case 0xb:
    case 0xe:
    case 0x13:
    case 0x14:
    case 0x15:
        func_020235e8(0x2485, 2, 1);
        break;
    case 1:
    case 2:
    case 3:
    case 6:
    case 7:
    case 9:
    case 10:
    case 0xf:
    case 0x12:
        func_020235e8(0x2485, 2, 2);
        break;
    case 4:
    case 8:
    case 0xc:
    case 0xd:
        func_020235e8(0x2485, 2, 3);
        break;
    }
    func_020235e8(0x2487, 5, (u16)nKind);
    return 1;
}
