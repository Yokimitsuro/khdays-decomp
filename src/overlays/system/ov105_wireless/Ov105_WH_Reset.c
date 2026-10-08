/* WH_Reset (wh.c): reset the wireless link (WH_StateInReset); on failure the helper goes to
 * WH_SYSSTATE_FATAL (0xa). */
extern int Ov105_WH_StateInReset(void);
extern void Ov105_WH_ChangeSysState(int);
void Ov105_WH_Reset(void) {
    if (Ov105_WH_StateInReset() == 0) {
        Ov105_WH_ChangeSysState(0xa);
    }
}
