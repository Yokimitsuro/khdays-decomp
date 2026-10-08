extern void Ov105_WH_ChangeSysState(int state);
extern int Ov105_WM_End(void *step);
extern void Ov105_WH_StateOutEnd(void);
/* WH_End (wh.c): go BUSY (3) and ask WM to end (WM_End with WH_StateOutEnd); a request
 * that does not start puts the helper in WH_SYSSTATE_ERROR (9) and returns FALSE. */
int Ov105_WH_End(void) {
    Ov105_WH_ChangeSysState(3);
    if (Ov105_WM_End(&Ov105_WH_StateOutEnd) != 2) {
        Ov105_WH_ChangeSysState(9);
        return 0;
    }
    return 1;
}
