/* Returns the number of players: in the session's member mask in a session, otherwise in the local
 * player mask. */

#include "game/engine.h"

extern unsigned short WH_GetBitmap(void);
extern int Ov008_CountPlayersInMask(void *value);

int Ov008_CountPlayers(void)
{
    unsigned short value;

    if (Session_Exists() != 0) {
        value = GetGlobalU16At6();
    } else {
        value = WH_GetBitmap();
    }

    return Ov008_CountPlayersInMask(&value);
}
