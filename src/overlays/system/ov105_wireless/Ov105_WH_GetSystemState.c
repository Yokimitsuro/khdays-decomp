/* WH_GetSystemState (wh.c): the helper's state, sSysState (WH_SYSSTATE_*). */

extern int data_ov105_020c04c0[];

int Ov105_WH_GetSystemState(void) {
    return data_ov105_020c04c0[9];
}
