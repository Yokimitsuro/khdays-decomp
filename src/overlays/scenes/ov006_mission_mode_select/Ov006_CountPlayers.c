/* Returns the number of players: in the session's member mask in a session, otherwise in the local
 * player mask. */

#include "game/engine.h"

extern unsigned short WH_GetBitmap(void);
extern int  Ov006_CountPlayersInMask(short *keys);

int Ov006_CountPlayers(void) {
    short keys;
    if (Session_Exists() != 0) {
        keys = (short)GetGlobalU16At6();
    } else {
        keys = (short)WH_GetBitmap();
    }
    return Ov006_CountPlayersInMask(&keys);
}
