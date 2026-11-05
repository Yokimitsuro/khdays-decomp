/* Ov021_EmblemFindPlayer -- Ov021_EmblemFindPlayer: the first player (0..ov022 020882f8) within
 * reach of the emblem, or -1.  Nothing while the shutdown hook says so (ov002 0206b7a4) or
 * outside a running scene (0206b758).  The reach is 0x3000 in mission 0x3b7 (ov002 0206b84c)
 * and 0x1800 elsewhere; a player counts when its actor (01fffde0) has bit 16 of its 64-bit
 * flags clear, owns a slot (ov022 02088474), sits in the emblem's bucket (the bucket's current
 * piece kind, ov002 02072754) and its seat (ov022 020881f8) is within reach of the emblem's
 * position (+0x2a8, VEC_Distance 01ff8e94). */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct Ov021PlayerActor {
    u64  nFlags;              /* 0x00: bit 16 = out of play */
} Ov021PlayerActor;

typedef struct Ov021Emblem {
    u8   pad_000[0x10];
    u8   nRoom;             /* 0x010 */
    u8   pad_011[0x2a8 - 0x11];
    VecFx32 position;         /* 0x2a8 */
} Ov021Emblem;

extern int   Ov002_RunShutdownHook(void);                               /* the shutdown hook's verdict */
extern int   Ov002_IsSessionOpen(void);                               /* scene running? */
extern int   Ov002_GetStateWord(void);                               /* the mission id */
extern int   func_ov022_020882f8(void);                               /* number of players */
extern int   Ov022_GetEntryField66(int nSeat);                          /* seat -> owner slot */
extern int   Ov002_GetSlotTableByte(int nGroup);                         /* a group's piece kind */
extern VecFx32 *func_ov022_020881f8(int nSeat);                       /* where the seat is */
extern int   VEC_Distance(VecFx32 *pA, VecFx32 *pB);                 /* VEC_Distance */

int Ov021_EmblemFindPlayer(Ov021Emblem *pSelf)
{
    int nPlayer;
    int nReach;
    Ov021PlayerActor *pActor;

    if (Ov002_RunShutdownHook() == 0 && Ov002_IsSessionOpen() != 0) {
        nReach = Ov002_GetStateWord() == 0x3b7 ? 0x3000 : 0x1800;
        for (nPlayer = 0; nPlayer < func_ov022_020882f8(); nPlayer++) {
            int nGroup;

            pActor = (Ov021PlayerActor *)GetEntryField20ByIndex(nPlayer);
            if ((pActor->nFlags & 0x10000) == 0 && (nGroup = Ov022_GetEntryField66(nPlayer)) >= 0 && pSelf->nRoom == Ov002_GetSlotTableByte(nGroup)) {
                if (VEC_Distance(func_ov022_020881f8(nPlayer), &pSelf->position) <= nReach) {
                    return nPlayer;
                }
            }
        }
    }
    return -1;
}
