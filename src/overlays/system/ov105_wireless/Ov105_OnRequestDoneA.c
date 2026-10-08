extern void Ov105_WH_SetError(unsigned int id);
extern int Ov105_PumpSubStateA(void);
extern void Ov105_WH_Reset(void);

/* If the request carries a target id, apply it and finish; otherwise try the fallback and only
 * finish when it declines. */
void Ov105_OnRequestDoneA(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        Ov105_WH_SetError(*(unsigned short *)(req + 2));
        Ov105_WH_Reset();
        return;
    }
    if (Ov105_PumpSubStateA() != 0) {
        return;
    }
    Ov105_WH_Reset();
}
