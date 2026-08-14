typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    void *pHead;
    void *pTail;
    u16 nCount;
    u16 nLinkOffset;
} NNSFndList;

/* The region at +0x32 is addressed as two-byte cells: the case-1 path shifts the
 * cell index left by one and reads the second byte, at +0x33. */
typedef struct {
    u8 bFirst;
    u8 bSecond;
} Ov002PanelCell;

typedef struct {
    u8 pad0000[8];
    int nField0008;         /* +0x08 */
    u8 pad000c[8];
    u16 wField0014;         /* +0x14 */
    u16 wField0016;         /* +0x16 */
    u8 pad0018[0x18];
    u8 bColumns;            /* +0x30 */
    u8 bCursorRow;          /* +0x31 */
    Ov002PanelCell aCells[0x227];   /* +0x32 */
    NNSFndList lists[3];    /* +0x480 */
    void *pCachedEntry;     /* +0x4a4 */
    u8 pad04a8[4];
    u8 bListRowBase;        /* +0x4ac */
    u8 bListRowOffset;      /* +0x4ad */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_020536bc(int nTag);
extern void func_ov002_020536dc(int nHandle, int nFlag);
extern int func_ov002_0205a3f0(int *pOut, int nCode);
extern int func_ov002_0205a638(void);
extern int func_ov002_0205a7b8(void);
extern void func_ov002_0205aa3c(int a, int b, int c, int d, int e);
extern void func_ov002_0205b6dc(int nHandle, int a, int b, int nFlag, int nValue);
extern int func_ov002_0205b728(int a, int b, int nKind);
extern u16 func_ov002_0205b778(NNSFndList *pList, int nIndex, int nKind, int nWhich);
extern void func_ov002_0205b640(int nTop, int nMain, int nValue, int nFlag,
                                int bMore);

void func_ov002_0205b7dc(int nMode, int nKind, int nFlag) {
    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nTop = func_ov002_020536bc(0xf);
    int nMain = func_ov002_020536bc(0xe);
    int nClass = func_ov002_0205a3f0(&nColumn, nMode);

    switch (nClass) {
    case 0:
        func_ov002_020536dc(nTop, 0);
        switch (nKind) {
        case 0:
            func_ov002_020536dc(nMain, 0);
            if (s->nField0008 != 0 && s->wField0014 == 0) {
                func_ov002_0205aa3c(3, s->wField0016, 0, 1, 1);
            }
            break;
        case 1: {
            int nValue = func_ov002_0205a638();

            func_ov002_0205b6dc(nMain, 0xb, 0x14, nFlag, nValue);
            break;
        }
        case 2: {
            int nValue = func_ov002_0205a7b8();

            func_ov002_0205b6dc(nMain, 0xb, 0x16, nFlag, nValue);
            break;
        }
        }
        break;

    case 1: {
        int nBase = nColumn * 6;
        int nValue = func_ov002_0205b728(s->aCells[nBase + 2].bSecond,
                                         s->aCells[nBase + 3].bSecond, nKind);

        func_ov002_0205b640(nTop, nMain, nValue, nFlag,
                            s->bCursorRow > nColumn + 1);
        break;
    }

    case 2: {
        u16 nValue = func_ov002_0205b778(&s->lists[0], nColumn * 6, nKind, 0);

        func_ov002_0205b640(nTop, nMain, nValue, nFlag,
                            s->bListRowBase + s->bListRowOffset > nColumn + 1);
        break;
    }

    case 3: {
        u16 nValue = func_ov002_0205b778(&s->lists[2], nColumn * 6, nKind, 1);

        func_ov002_0205b640(nTop, nMain, nValue, nFlag,
                            s->bListRowOffset > nColumn + 1);
        break;
    }

    case 4:
    case 5:
        func_ov002_020536dc(nMain, 0);
        func_ov002_020536dc(nTop, 0);
        break;
    }
}
