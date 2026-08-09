extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern char *data_02044748;

/* Length of the pending sound-command list. */
int SND_CountReservedCommand(void) {
    int enabled = OS_DisableInterrupts();
    int count = 0;
    char *cmd = *(char **)&data_02044748;
    while (cmd != 0) {
        cmd = *(char **)cmd;
        count++;
    }
    OS_RestoreInterrupts(enabled);
    return count;
}
