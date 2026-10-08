/* WM_GetAllowedChannel (NitroSDK wm_etc.c): the channels the firmware allows, from the
 * user settings at 0x027ffcfa, or 0x8000 when WM is not initialised. */
extern int Ov105_WMi_CheckInitialized(void);
int Ov105_WM_GetAllowedChannel(void) {
    if (Ov105_WMi_CheckInitialized() != 0) {
        return 0x8000;
    }
    return *(unsigned short *)0x27ffcfa;
}
