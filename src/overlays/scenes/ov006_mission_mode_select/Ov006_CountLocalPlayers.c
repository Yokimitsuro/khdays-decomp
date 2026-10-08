/* Returns the number of players in the local player mask (WH_GetBitmap). */

extern unsigned short WH_GetBitmap(void);
extern int Ov006_CountPlayersInMask(short *p);
int Ov006_CountLocalPlayers(void) {
    short mask = WH_GetBitmap();
    return Ov006_CountPlayersInMask(&mask);
}
