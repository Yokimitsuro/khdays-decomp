extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern char *data_ov105_020bfa20;

/* WM_GetConnectedAIDs (NitroSDK): the bitmap of the connected AIDs in WM's status (0
 * without WM). */
unsigned short Ov105_WM_GetConnectedAIDs(void) {
    int enabled = OS_DisableInterrupts();
    char *session = *(char **)((char *)&data_ov105_020bfa20 + 4);
    int value;
    if (session != 0) {
        value = *(int *)(session + 0x14c);
    } else {
        value = 0;
    }
    OS_RestoreInterrupts(enabled);
    return (unsigned short)value;
}
