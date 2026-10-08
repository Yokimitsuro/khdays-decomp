/* WH_StateInReset (wh.c): go BUSY (3) and ask WM to reset (WM_Reset with
 * WH_StateOutReset); TRUE while the request runs, else record the error and FALSE. */
extern void Ov105_WH_ChangeSysState(int mode);
extern int Ov105_WM_Reset(void *cb);
extern void Ov105_WH_SetError(int result);
extern void Ov105_WH_StateOutReset(void);

int Ov105_WH_StateInReset(void) {
    int r;

    Ov105_WH_ChangeSysState(3);
    r = Ov105_WM_Reset(&Ov105_WH_StateOutReset);
    if (r == 2) {
        return 1;
    }
    Ov105_WH_SetError(r);
    return 0;
}
