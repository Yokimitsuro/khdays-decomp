/* Ov021_EmblemHandleMessage -- Ov021_EmblemHandleMessage: the emblem's message handler; only type 0
 * (a player reached it) does anything.  Records the player (+0x2bc, the message byte at +4),
 * resets the spiral (+0x2be = 0) and picks its direction (+0x2bd): +1 in a session (02030670),
 * otherwise +1 or -1 at random (Rand16NextScaled 02023e80); state 2.  Then, inside a running
 * scene (ov002 0206b758): when the player is the local peer (01fffe14) the pickup sound plays
 * (02033b24 pair 0 / 0xf); otherwise, if the local peer's owner slot (ov022 02088474) is the
 * bucket's current piece kind (ov002 02072754), the pickup effect (slot 0 / kind 0xf) is
 * spawned where that peer sits (ov022 020881f8; 02033d0c). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov021EmblemMessage {
    u8   nType;               /* 0x00: 0 = reached */
    u8   pad_01[3];
    char nPlayer;             /* 0x04 */
} Ov021EmblemMessage;

typedef struct Ov021Emblem {
    u8   pad_000[0x10];
    u8   nRoom;             /* 0x010 */
    u8   pad_011[0x2b4 - 0x11];
    u8   nState;              /* 0x2b4 */
    u8   pad_2b5[7];
    char nPlayer;             /* 0x2bc */
    char nDirection;          /* 0x2bd: +1 / -1 */
    u16  nSpiral;             /* 0x2be */
} Ov021Emblem;

extern int   Session_IsActive(void);                                     /* Session_IsActive */
extern int   Rand16NextScaled(int nRange);                               /* Rand16NextScaled */
extern int   Ov002_IsSessionOpen(void);                               /* scene running? */
extern int   QueryActiveStateOrDelegate(void);                                     /* the local peer */
extern void  PlaySoundChecked(int nPair, int nArg);                      /* PlaySoundChecked */
extern int   Ov022_GetEntryField66(int nSeat);                          /* seat -> owner slot */
extern int   Ov002_GetSlotTableByte(int nGroup);                         /* a group's piece kind */
extern VecFx32 *func_ov022_020881f8(int nSeat);                       /* where the seat is */
extern int   Slot_Spawn(int nSlot, int nId, VecFx32 *pPos, unsigned int nFlags); /* Slot_Spawn */

void Ov021_EmblemHandleMessage(Ov021Emblem *pSelf, Ov021EmblemMessage *pMessage)
{
    if (pMessage->nType != 0) {
        return;
    }
    pSelf->nPlayer = pMessage->nPlayer;
    pSelf->nSpiral = 0;
    pSelf->nDirection = Session_IsActive() != 0 ? 1 : (Rand16NextScaled(2) != 0 ? -1 : 1);
    pSelf->nState = 2;
    if (Ov002_IsSessionOpen() == 0) {
        return;
    }
    if (pSelf->nPlayer == QueryActiveStateOrDelegate()) {
        PlaySoundChecked(0, 0xf);
        return;
    }
    if (pSelf->nRoom != Ov002_GetSlotTableByte(Ov022_GetEntryField66(QueryActiveStateOrDelegate()))) {
        return;
    }
    Slot_Spawn(0, 0xf, func_ov022_020881f8(QueryActiveStateOrDelegate()), 0);
}
