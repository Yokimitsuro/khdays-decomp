typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

typedef struct Ov002Vec3 {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct Ov002DayEntry {
    char pad000[1];
    u8 bDay;                /* replaces the name's day when bit 15 is raised */
    char pad002[2];
    u16 hFlags;
} Ov002DayEntry;

typedef struct Ov002CodeBase {
    char pad000[0x2f];
    s8 aSlots[4];
} Ov002CodeBase;

typedef struct Ov002PlaceResult {
    char pad000[8];
    int nX;
    int nY;
    int nZ;
    int nExtra;
} Ov002PlaceResult;

extern Ov002CodeBase *data_ov002_0207fa10;
extern char data_ov002_0207f108[];      /* "%s%02d_%d" */
extern char data_ov002_0207f100[];      /* "pent" */

extern Ov002DayEntry *func_ov002_02071420(int nDay, int nSlotValue);
extern void OS_SPrintf(char *pDest, const char *pFmt, ...);
extern Ov002PlaceResult *func_0202c3c4(u16 nSlot, const char *pKey);

/* Builds a placement key out of the mission name and looks the placement up.
   The day comes from characters 4 and 5 of the name read as two decimal digits,
   unless the peer row says otherwise.  The key is "pent<day>_<index>". */
void func_ov002_02072874(const char *pName, int nSlot, Ov002Vec3 *pPlace,
                         int *pOutExtra, int nIndex)
{
    Ov002CodeBase *pBase;
    Ov002DayEntry *pEntry;
    Ov002PlaceResult *pResult;
    int nDay;
    char szKey[0x10];

    nDay = (pName[4] - '0') * 10 + (pName[5] - '0');
    pBase = data_ov002_0207fa10;
    pEntry = func_ov002_02071420(nDay, pBase->aSlots[nSlot]);
    if ((pEntry->hFlags & 0x8000) != 0) {
        nDay = pEntry->bDay;
    }

    OS_SPrintf(szKey, data_ov002_0207f108, data_ov002_0207f100, nDay, nIndex);
    pResult = func_0202c3c4((u16)nSlot, szKey);
    pPlace->x = pResult->nX;
    pPlace->y = pResult->nY;
    pPlace->z = pResult->nZ;
    *pOutExtra = pResult->nExtra;
}
