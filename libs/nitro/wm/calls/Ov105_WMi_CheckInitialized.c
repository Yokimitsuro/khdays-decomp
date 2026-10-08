extern char data_ov105_020bfa20[];
/* WMi_CheckInitialized (NitroSDK wm_system.c): WM_ERRCODE_ILLEGAL_STATE (3) until
 * WM is initialised, else success. */
int Ov105_WMi_CheckInitialized(void) {
    if (*(unsigned short *)data_ov105_020bfa20 != 0) {
        return 0;
    }
    return 3;
}
