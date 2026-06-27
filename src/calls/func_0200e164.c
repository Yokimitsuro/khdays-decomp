extern int WM_EndKeySharing_0x0200e918(void);
extern void WM_EndKeySharing_0x0200e90c(void);
extern void CARDi_UnlockResource(int resource, int kind);

void func_0200e164(int resource) {
    if (WM_EndKeySharing_0x0200e918() == 0)
        WM_EndKeySharing_0x0200e90c();
    CARDi_UnlockResource(resource, 2);
}
