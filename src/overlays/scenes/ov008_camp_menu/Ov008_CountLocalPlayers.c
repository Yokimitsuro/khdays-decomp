/* Returns the number of players in the local player mask (WH_GetBitmap). */

extern unsigned short WH_GetBitmap(void);
extern int Ov008_CountPlayersInMask(short *);
int Ov008_CountLocalPlayers(void)
{
    short mask = WH_GetBitmap();
    return Ov008_CountPlayersInMask(&mask);
}
