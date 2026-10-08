extern int Ov105_WM_EndScan(void *handler);
extern void Ov105_WH_SetError(int id);
extern void Ov105_WH_StateOutEndScan(int req);
/* Pump the sub-state with its handler; unless it reports 2 (still running), publish the result
 * and report done. */
int Ov105_PumpSubStateB(void) {
    int r = Ov105_WM_EndScan(&Ov105_WH_StateOutEndScan);
    if (r != 2) {
        Ov105_WH_SetError(r);
        return 0;
    }
    return 1;
}
