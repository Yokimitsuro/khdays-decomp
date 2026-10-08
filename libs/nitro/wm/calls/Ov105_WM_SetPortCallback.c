extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void OS_GetMacAddress(void *dst);
extern int Ov105_WMi_CheckInitialized(void);
extern char *Ov105_WMi_GetSystemWork(void);
extern unsigned short Ov105_WM_GetConnectedAIDs(void);
extern int Ov105_WM_GetAID(void);

/* WM_SetPortCallback (NitroSDK wm_standard.c): set the receive callback of a port and its
 * argument, and call it at once with a WM_STATECODE_PORT_INIT record that carries this
 * console's AID (WM_GetAID, +0x20) and the connected AIDs (WM_GetConnectedAIDs, +0x22). */
int Ov105_WM_SetPortCallback(unsigned short port, void (*callback)(void *), void *arg) {
    char event[0x44];
    char *state;
    int enabled;
    int err;
    if (callback != 0) {
        MI_CpuFill8(event, 0, 0x44);
        *(short *)event = 0x82;
        *(short *)(event + 2) = 0;
        *(short *)(event + 4) = 0x19;
        *(short *)(event + 6) = (short)port;
        *(int *)(event + 8) = 0;
        *(int *)(event + 0xc) = 0;
        *(short *)(event + 0x10) = 0;
        *(unsigned short *)(event + 0x1a) = 0xffff;
        *(void **)(event + 0x1c) = arg;
        *(short *)(event + 0x12) = 0;
        OS_GetMacAddress(event + 0x14);
    }
    enabled = OS_DisableInterrupts();
    err = Ov105_WMi_CheckInitialized();
    if (err != 0) {
        OS_RestoreInterrupts(enabled);
        return err;
    }
    state = Ov105_WMi_GetSystemWork() + port * 4;
    *(void **)(state + 0xcc) = (void *)callback;
    *(void **)(state + 0x10c) = arg;
    if (callback != 0) {
        *(short *)(event + 0x22) = (short)Ov105_WM_GetConnectedAIDs();
        *(short *)(event + 0x20) = (short)Ov105_WM_GetAID();
        callback(event);
    }
    OS_RestoreInterrupts(enabled);
    return 0;
}
