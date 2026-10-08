/* WM_StartParent (NitroSDK): WMi_StartParentEx with powerSave TRUE. */
extern int Ov105_WMi_StartParentEx(int a, int b);
int Ov105_WM_StartParent(int param_1) {
    return Ov105_WMi_StartParentEx(param_1, 1);
}
