/* Ov008_StoreSeatCampRecord -- store the local seat's 6-byte camp record (+2 bit 1: game flag 0x2010,
 * the dual wield; +4 the seat's character) in the camp's context (data_ov008_02090f00) and send it
 * to the room. Bails out if the context is not allocated or there is no session. A given record is
 * first copied into the context's "current" one (+0x46); then, if Ov008_IsSessionReady() reports
 * the session ready, the current record goes to the seat's (+0x2e + 6 x seat) and mode 3 is sent
 * (Ov008_SendMenuMessage), otherwise mode 2. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct SeatCampRecord {
    u16 w0;          /* 0x0 */
    u16 wFlags;      /* 0x2: bit 1 = game flag 0x2010, the dual wield */
    u16 wCharacter;  /* 0x4: the seat's character */
} SeatCampRecord;

typedef struct CampSeatRecords {
    u8          pad_0000[0x2e];
    SeatCampRecord entries[4];   /* 0x2e: each seat's record, stride 6 */
    SeatCampRecord cur;          /* 0x46: the record being sent */
} CampSeatRecords;

extern CampSeatRecords *data_ov008_02090f00;
extern int  Ov008_IsSessionReady(void);
extern void Ov008_SendMenuMessage(int mode);

void Ov008_StoreSeatCampRecord(SeatCampRecord *pRecord)
{
    int idx = Session_GetLocalPlayerIndex();
    if (data_ov008_02090f00 == 0) return;
    if (Session_Exists() == 0) return;
    if (pRecord != 0) {
        CampSeatRecords *g = data_ov008_02090f00;
        g->cur = *pRecord;
    }
    if (Ov008_IsSessionReady() != 0) {
        CampSeatRecords *g = data_ov008_02090f00;
        g->entries[idx] = g->cur;
        Ov008_SendMenuMessage(3);
    } else {
        Ov008_SendMenuMessage(2);
    }
}
