extern void Ov105_WH_ChangeSysState(int state);
extern short Ov105_SelectChannel(unsigned int id);
extern char data_ov105_020c04c0[];
/* WH_GetMeasureChannel (wh.c): back to IDLE, pick the channel among the ones that
 * measured least busy (SelectChannel over the channel bitmap) and return it. */
unsigned short Ov105_WH_GetMeasureChannel(void) {
    Ov105_WH_ChangeSysState(1);
    *(short *)(data_ov105_020c04c0 + 2) =
        Ov105_SelectChannel(*(unsigned short *)(data_ov105_020c04c0 + 10));
    return *(unsigned short *)(data_ov105_020c04c0 + 2);
}
