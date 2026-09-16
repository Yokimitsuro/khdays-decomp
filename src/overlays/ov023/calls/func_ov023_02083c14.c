/* func_ov023_02083c14 -- Ov023_RequestGroupResources: request the resources the event's actor
 * group needs.  The group (0202bfa0 on the u16 id) lists entries whose 13-bit kind mask (+0x70)
 * selects, per set bit, a pair of resource ids from data_ov023_02089d74 (0x18c.. / 0x198..,
 * Res_RequestIdPair 0203355c).  With the extra flag the pair 0x197 / 0x1a3 is requested too and
 * the root byte data_ov023_0208a784[0] set, else cleared; when nothing at all was requested
 * the default pair 0x18d / 0x199 is. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov023GroupEntry {
    u8   pad_00[0x70];
    int  nKindMask;           /* 0x70 */
} Ov023GroupEntry;

typedef struct Ov023Group {
    u16  wField00;            /* 0x00 */
    u16  wCount;              /* 0x02 */
    Ov023GroupEntry **apEntry; /* 0x04 */
} Ov023Group;

typedef struct Ov023ResPair {
    int  nFirst;              /* 0x00 */
    int  nSecond;             /* 0x04 */
} Ov023ResPair;

typedef struct Ov023KindResTable {
    Ov023ResPair aPair[13];   /* 0x00 */
} Ov023KindResTable;

typedef struct Ov023SceneRoot {
    u8   bExtraRequested;     /* 0x00 */
    u8   pad_01[3];
    void *pScene;             /* 0x04 */
} Ov023SceneRoot;

extern Ov023Group *func_0202bfa0(u16 nGroup);                       /* the actor group by id */
extern void  func_0203355c(int nId);                                /* Res_RequestIdPair */
extern const Ov023KindResTable data_ov023_02089d74;                 /* resource pair per kind bit */
extern Ov023SceneRoot data_ov023_0208a784;

void func_ov023_02083c14(int nGroup, int bExtra)
{
    int bAny;
    int i;
    Ov023Group *pGroup;
    Ov023GroupEntry *pEntry;
    int j;

    bAny = 0;
    pGroup = func_0202bfa0(nGroup);
    for (i = 0; i < pGroup->wCount; i++) {
        pEntry = pGroup->apEntry[i];
        for (j = 0; j <= 12; j++) {
            if (pEntry->nKindMask & (1 << j)) {
                func_0203355c(data_ov023_02089d74.aPair[j].nFirst);
                func_0203355c(data_ov023_02089d74.aPair[j].nSecond);
                bAny = 1;
            }
        }
    }
    if (bExtra != 0) {
        func_0203355c(0x197);
        func_0203355c(0x1a3);
        bAny = 1;
        data_ov023_0208a784.bExtraRequested = 1;
    } else {
        data_ov023_0208a784.bExtraRequested = 0;
    }
    if (bAny == 0) {
        func_0203355c(0x18d);
        func_0203355c(0x199);
    }
}
