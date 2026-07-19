extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OSi_InsertThreadByPriority(void *thread);
extern void OSi_RescheduleThread(void);
extern char data_0204430c;
extern char data_02044340;

/* Moves a thread off the "waiting to be destroyed" list and back onto the run queue, recording the
 * exit value it is waiting on. */
int OSi_WaitOnExitProc(char *thread, void *arg) {
    char *cur = *(char **)((char *)&data_0204430c + 0x2c);
    char *prev = 0;
    int enabled = OS_DisableInterrupts();
    while (cur != 0 && cur != thread) {
        prev = cur;
        cur = *(char **)(cur + 0x68);
    }
    if (cur == 0 || cur == (char *)&data_02044340) {
        OS_RestoreInterrupts(enabled);
        return 0;
    }
    if (*(void **)(cur + 0x70) != arg) {
        if (prev == 0) {
            *(char **)((char *)&data_0204430c + 0x2c) = *(char **)(thread + 0x68);
        } else {
            *(char **)(prev + 0x68) = *(char **)(thread + 0x68);
        }
        *(void **)(thread + 0x70) = arg;
        OSi_InsertThreadByPriority(thread);
        OSi_RescheduleThread();
    }
    OS_RestoreInterrupts(enabled);
    return 1;
}
