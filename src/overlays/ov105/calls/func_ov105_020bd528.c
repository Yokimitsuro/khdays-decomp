extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern char *data_ov105_020bfa20;

/* Aggregate link state of the active session (0 when there is none). */
unsigned short func_ov105_020bd528(void) {
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
