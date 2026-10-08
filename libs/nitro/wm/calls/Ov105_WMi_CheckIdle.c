extern int Ov105_WMi_CheckInitialized(void);
extern void DC_InvalidateRange(void *addr, unsigned int size);
extern char data_ov105_020bfa20[];
/* WMi_CheckIdle (NitroSDK wm_system.c): WM_ERRCODE_ILLEGAL_STATE (3) unless WM is
 * initialised and its state is past WM_STATE_STOP. */
int Ov105_WMi_CheckIdle(void) {
    int r = Ov105_WMi_CheckInitialized();
    if (r == 0) {
        DC_InvalidateRange(*(void **)(*(int *)(data_ov105_020bfa20 + 4) + 4), 2);
        if (**(unsigned short **)(*(int *)(data_ov105_020bfa20 + 4) + 4) <= 1) {
            r = 3;
        } else {
            r = 0;
        }
        return r;
    }
    return r;
}
