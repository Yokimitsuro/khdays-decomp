
#include "nitro/types.h"
#include "nitro/fx_types.h"

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
extern char gOv002StrIntIntFmt[];      /* "%s%02d_%d" */
extern char gOv002PentName[];      /* "pent" */

extern Ov002DayEntry *Ov002_FindPeerRow(int nDay, int nSlotValue);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern Ov002PlaceResult *EntityMgr_FindCollEntry(int nSlot, const char *pKey);

/* Builds a placement key out of the mission name and looks the placement up.
   The day comes from characters 4 and 5 of the name read as two decimal digits,
   unless the peer row says otherwise.  The key is "pent<day>_<index>". */
void Ov002_ResolveNamedPlacement(const char *pName, int nSlot, VecFx32 *pPlace,
                         int *pOutExtra, int nIndex)
{
    Ov002CodeBase *pBase;
    Ov002DayEntry *pEntry;
    Ov002PlaceResult *pResult;
    int nDay;
    char szKey[0x10];

    nDay = (pName[4] - '0') * 10 + (pName[5] - '0');
    pBase = data_ov002_0207fa10;
    pEntry = Ov002_FindPeerRow(nDay, pBase->aSlots[nSlot]);
    if ((pEntry->hFlags & 0x8000) != 0) {
        nDay = pEntry->bDay;
    }

    OS_SPrintf(szKey, gOv002StrIntIntFmt, gOv002PentName, nDay, nIndex);
    pResult = EntityMgr_FindCollEntry((u16)nSlot, szKey);
    pPlace->x = pResult->nX;
    pPlace->y = pResult->nY;
    pPlace->z = pResult->nZ;
    *pOutExtra = pResult->nExtra;
}
