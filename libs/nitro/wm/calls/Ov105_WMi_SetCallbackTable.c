extern char data_ov105_020bfa20[];
/* WMi_SetCallbackTable (NitroSDK wm_system.c): the callback of one API id. */
void Ov105_WMi_SetCallbackTable(int idx, int value) {
    *(int *)(*(int *)(data_ov105_020bfa20 + 4) + idx * 4 + 0x18) = value;
}
