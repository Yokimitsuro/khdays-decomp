/* Ov025_Reports_IsDaySpanComplete -- Ov025_Reports_IsDaySpanComplete: are all the missions of the day span
 * pSpan (first day, last day) done?  Every visible entry of the mission list (0208a1cc) whose
 * day (+0x1c) lies in the span must have rank 3 in game-state field 0x28e4 + 3 * id, and every
 * entry of the challenge list in the span, other than status 4 (+0x18), must have a non-zero
 * field 0x2a4c + 3 * id.  Returns 1 / 0; the reports page unlocks the read variant of a report
 * with it (0209f860).  Codegen: the two bounds are int locals (u16 locals are coloured after
 * the entry pointer and swap r4..r6). */

#include "nitro/types.h"

typedef struct Ov008MissionListState {
    u8   data[0x24];
} Ov008MissionListState;

typedef struct Ov008MissionListEntry {
    u16  nFileNumber;               /* 0x00 */
    u16  nMissionId;          /* 0x02 */
    u8   pad_04[0x14];
    int  nKind;             /* 0x18 */
    int  nDay;                /* 0x1c */
} Ov008MissionListEntry;

extern Ov008MissionListEntry *Ov025_FindListObjectWithField10Zero(Ov008MissionListState *pList, Ov008MissionListEntry *pEntry); /* Ov025_MissionList_NextVisible */
extern u32   GameState_GetField(int nField, int nBits);                  /* GameState_GetField */

int Ov025_Reports_IsDaySpanComplete(Ov008MissionListState *pMissions, Ov008MissionListState *pChallenges, const u16 *pSpan)
{
    int nFirstDay;
    int nLastDay;
    Ov008MissionListEntry *pEntry;

    nFirstDay = pSpan[0];
    nLastDay = pSpan[1];
    for (pEntry = Ov025_FindListObjectWithField10Zero(pMissions, 0); pEntry != 0; pEntry = Ov025_FindListObjectWithField10Zero(pMissions, pEntry)) {
        if (pEntry->nDay >= nFirstDay && pEntry->nDay <= nLastDay && GameState_GetField(pEntry->nMissionId * 3 + 0x28e4, 3) < 3) {
            return 0;
        }
    }
    for (pEntry = Ov025_FindListObjectWithField10Zero(pChallenges, 0); pEntry != 0; pEntry = Ov025_FindListObjectWithField10Zero(pChallenges, pEntry)) {
        if (pEntry->nDay >= nFirstDay && pEntry->nDay <= nLastDay && pEntry->nKind != 4 && GameState_GetField(pEntry->nMissionId * 3 + 0x2a4c, 3) == 0) {
            return 0;
        }
    }
    return 1;
}
