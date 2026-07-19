extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern char *data_ov105_020bfa20;

/* Current wireless channel of the active session (0 when there is none). */
int func_ov105_020bd4f8(void) {
    int enabled = OS_DisableInterrupts();
    char *session = *(char **)((char *)&data_ov105_020bfa20 + 4);
    unsigned short value;
    if (session != 0) {
        value = *(unsigned short *)(session + 0x150);
    } else {
        value = 0;
    }
    OS_RestoreInterrupts(enabled);
    return value;
}
