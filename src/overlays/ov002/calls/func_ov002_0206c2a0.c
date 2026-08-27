typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct Ov002TallyRow {
    int aCounters[11];      /* one per tally kind, indexed by the kind */
} Ov002TallyRow;

typedef struct Ov002SessionBlock {
    int nSessionToken;      /* -1 while nothing is held */
    char pad004[4];
    Ov002TallyRow aTallyRows[16];
} Ov002SessionBlock;

typedef struct Ov002RequestBlock {
    char pad000[0xc];
    int nRequestParam;      /* the ceiling the running total is clamped to */
    char pad010[4];
    int nRunningTotal;
    char pad018[2];
    s8 bRequestId;
    char pad01b[0x59];
    s16 nRequestCountdown;  /* the total has to reach this */
} Ov002RequestBlock;

typedef struct Ov002TallyRequest {
    u8 nKind;               /* which counter to move and which arm to run */
    u8 nOwner;              /* which row owns it; 0xf means no owner */
    char pad002[2];
    int nAmount;
} Ov002TallyRequest;

extern char *data_ov002_0207fa00;
extern u8 data_0204c240;                        /* boot-mode flags */

extern void func_ov002_020679c4(int nAmount, s16 *pA, s16 *pB);
extern int func_020235d0(int nFlag, int nWidth);
extern void func_020235e8(int nFlag, int nWidth, int nValue);
extern int func_ov002_0206b864(void);           /* a peer id is assigned */
extern int func_ov002_0205a188(int nIndex);     /* find the list entry */
extern void func_ov002_0205a248(int pEntry, int nValue);
extern void func_ov002_02061cac(int nAmount);   /* push the marker number */
extern int func_01fffe14(void);                 /* the local peer */
extern void func_ov002_02057620(int nOwner);    /* cancel the owner's slot */
extern int func_ov002_02061b80(void);
extern void func_ov002_02061978(int a, int b, int c);
extern int func_ov022_020882f8(void);           /* how many entries are live */
extern int func_020358f4(int nEntry, int nWhat);
extern int func_ov022_020882e0(int nEntry);
extern void func_ov022_02088bec(int nEntry, int nAmount);
extern int func_02020a9c(void);
extern void func_ov002_020574a4(int nTotal, int a);
extern int func_02023588(int nFlag);
extern void func_020235a8(int nFlag);

/* Moves one tally counter and then runs whatever its kind asks for.  Kind 2
   splits the amount into two halves and uses their sum; every other kind takes
   the amount as it stands.  The counter is clamped at zero below and, above, at
   99999 for kind 5, 9999 for kind 7 and 999999 for everything else. */
void func_ov002_0206c2a0(Ov002TallyRequest *pReq)
{
    char *pRoot;
    Ov002SessionBlock *pSession;
    Ov002RequestBlock *pRequest;
    s16 *pState;
    int nAmount;
    int nRow;
    int nCount;
    int nOwner;
    int nStamp;
    int nValue;
    int i;
    s16 hA;
    s16 hB;

    pRoot = data_ov002_0207fa00;
    pSession = (Ov002SessionBlock *)(pRoot + 0x8bcc);
    nOwner = pReq->nOwner;
    pRequest = (Ov002RequestBlock *)(pRoot + 0x8c94);
    pState = (s16 *)(pRoot + 0x8ba8);
    if (nOwner == 0xf) {
        nOwner = -1;
    }
    hA = 0;
    hB = 0;
    nRow = pReq->nOwner;

    switch (pReq->nKind) {
    case 2:
        func_ov002_020679c4(pReq->nAmount, &hA, &hB);
        nAmount = hA + hB;
        break;
    default:
        nAmount = pReq->nAmount;
        break;
    }

    nValue = pSession->aTallyRows[nRow].aCounters[pReq->nKind];
    nValue = nValue + nAmount;
    if (nValue < 0) {
        nValue = 0;
    } else if (pReq->nKind == 5 && nValue > 99999) {
        nValue = 99999;
    } else if (pReq->nKind == 7 && nValue > 9999) {
        nValue = 9999;
    } else if (nValue > 999999) {
        nValue = 999999;
    }
    pSession->aTallyRows[nRow].aCounters[pReq->nKind] = nValue;

    switch (pReq->nKind) {
    case 0:
        nCount = func_020235d0(0x20a9, 4);
        if (nCount > 0) {
            nStamp = func_020235d0(0x208f, 0xa);
            nStamp = nStamp + pReq->nAmount;
            func_020235e8(0x208f, 0xa, (u16)nStamp);
            if (pSession->nSessionToken != -1 && func_ov002_0206b864() != 0) {
                func_ov002_0205a248(func_ov002_0205a188((u8)(nCount - 1)),
                                    nStamp);
            }
        }
        if ((data_0204c240 & 4) != 0 && pSession->nSessionToken != -1
            && func_ov002_0206b864() != 0) {
            func_ov002_02061cac(pReq->nAmount);
        }
        break;

    case 3:
        if (*pState == 0x6c) {
            nCount = func_020235d0(0x20a9, 4);
            if (nCount > 0) {
                nStamp = func_020235d0(0x208f, 0xa);
                nStamp = nStamp + pReq->nAmount;
                func_020235e8(0x208f, 0xa, (u16)nStamp);
                if (pSession->nSessionToken != -1
                    && func_ov002_0206b864() != 0) {
                    func_ov002_0205a248(func_ov002_0205a188((u8)(nCount - 1)),
                                        nStamp);
                }
            }
        }
        break;

    case 7:
        if ((data_0204c240 & 4) != 0 && pSession->nSessionToken != -1
            && func_ov002_0206b864() != 0) {
            if (nOwner == func_01fffe14()) {
                func_ov002_02061cac(pReq->nAmount);
            }
            if (nOwner != -1 && nAmount > 0) {
                func_ov002_02057620(pReq->nOwner);
            }
        }
        break;

    case 2:
        if (pSession->nSessionToken != -1 && func_ov002_0206b864() != 0
            && func_ov002_02061b80() != 0) {
            func_ov002_02061978(hA, hB, 1);
        }
        break;
    }

    /* Kind 2 also crosses every three hundred: when the counter moves into a
       new bucket, every live entry gets bumped. */
    if (pReq->nKind == 2 && pSession->nSessionToken != -1
        && func_ov002_0206b864() != 0) {
        nStamp = pSession->aTallyRows[pReq->nOwner].aCounters[2];
        nValue = nStamp - nAmount;
        if (nValue / 300 != nStamp / 300) {
            for (i = 0; i < func_ov022_020882f8(); i++) {
                if (func_020358f4(i, 0x51) != 0
                    && func_ov022_020882e0(i) > 0) {
                    func_ov022_02088bec(i, 0x2710);
                }
            }
        }
    }

    if (pRequest->bRequestId == 2 && pReq->nKind == 2) {
        nAmount = hA;
    }
    if (!((pRequest->bRequestId == 2 && pReq->nKind == 2)
          || (pRequest->bRequestId == 0 && pReq->nKind == 3)
          || (pRequest->bRequestId == 4 && pReq->nKind == 3)
          || (pRequest->bRequestId == 1 && pReq->nKind == 3))) {
        return;
    }

    pRequest->nRunningTotal = pRequest->nRunningTotal + nAmount;
    if (pRequest->nRequestParam <= pRequest->nRunningTotal) {
        pRequest->nRunningTotal = pRequest->nRequestParam;
    }

    if (pSession->nSessionToken != -1 && func_ov002_0206b864() != 0
        && func_02020a9c() != 0x2a) {
        func_ov002_020574a4(pRequest->nRunningTotal, 1);
    }

    if (pSession->nSessionToken == -1) {
        return;
    }
    if (func_ov002_0206b864() == 0) {
        return;
    }
    if (func_ov022_020882f8() <= 1) {
        return;
    }
    if ((data_0204c240 & 4) == 0) {
        return;
    }
    if (func_02023588(0x20dc) != 0) {
        return;
    }
    if (pRequest->nRunningTotal < pRequest->nRequestCountdown) {
        return;
    }
    func_020235a8(0x20dc);
}
