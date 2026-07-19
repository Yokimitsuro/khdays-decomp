extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OS_WakeupThread(void *queue);
extern int FSi_TranslateCommand(void *file, int command);
extern void *FSi_NextCommand(void *arc);

static inline int FSi_IsCancelRequested(char *file) {
    return (*(volatile int *)(file + 0xc) & 4) != 0;
}

/* Runs the archive's queued commands one after another until the queue drains, a command asks to
 * be finished asynchronously, or somebody cancels. */
void FSi_ExecuteAsyncCommand(char *file) {
    char *arc;
    int enabled;
    arc = *(char **)(file + 8);
    if (file == 0) {
        return;
    }
    for (;;) {
        enabled = OS_DisableInterrupts();
        *(volatile int *)(file + 0xc) |= 0x40;
        if (FSi_IsCancelRequested(file)) {
            OS_WakeupThread(file + 0x18);
            OS_RestoreInterrupts(enabled);
            return;
        }
        *(volatile int *)(file + 0xc) |= 8;
        OS_RestoreInterrupts(enabled);
        if (FSi_TranslateCommand(file, *(int *)(file + 0x10)) == 6) {
            return;
        }
        file = FSi_NextCommand(arc);
        if (file == 0) {
            return;
        }
    }
}
