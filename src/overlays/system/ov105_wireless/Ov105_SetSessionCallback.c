extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern int Ov105_WMi_CheckInitialized(void);
extern char *Ov105_WMi_GetSystemWork(void);

/* Records the caller's callback on the wireless session, if the session is idle enough to take it. */
int Ov105_SetSessionCallback(int callback) {
    int enabled = OS_DisableInterrupts();
    int err = Ov105_WMi_CheckInitialized();
    if (err != 0) {
        OS_RestoreInterrupts(enabled);
        return err;
    }
    *(int *)(Ov105_WMi_GetSystemWork() + 0xc8) = callback;
    OS_RestoreInterrupts(enabled);
    return 0;
}
