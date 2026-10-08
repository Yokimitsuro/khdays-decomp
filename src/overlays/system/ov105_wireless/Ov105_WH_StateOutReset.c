extern void Ov105_WH_ChangeSysState(int state);
extern void Ov105_WH_SetError(unsigned int id);
extern void Ov105_WH_FreeBuffers(void);
/* WH_StateOutReset (wh.c): WM_Reset's callback. An error code puts the helper in
 * WH_SYSSTATE_ERROR (9) and records it; otherwise the buffers are freed and it goes IDLE (1). */
void Ov105_WH_StateOutReset(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        Ov105_WH_ChangeSysState(9);
        Ov105_WH_SetError(*(unsigned short *)(req + 2));
        return;
    }
    Ov105_WH_FreeBuffers();
    Ov105_WH_ChangeSysState(1);
}
