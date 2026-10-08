/* WMi_GetSystemWork (NitroSDK wm_system.c): WM's ARM9 work block. */

extern int data_ov105_020bfa20;
int Ov105_WMi_GetSystemWork(void) {
    return *(int *)((char *)&data_ov105_020bfa20 + 4);
}
