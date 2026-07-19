extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern char data_020463cc;

/* Takes the PXI command lock if it is free. */
int PXIi_TryLock(void) {
    int enabled = OS_DisableInterrupts();
    if (*(int *)((char *)&data_020463cc + 0x1c) != 0) {
        OS_RestoreInterrupts(enabled);
        return 0;
    }
    *(int *)((char *)&data_020463cc + 0x1c) = 1;
    OS_RestoreInterrupts(enabled);
    return 1;
}
