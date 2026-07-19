extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern void OS_WakeupThread(void *queue);

/* Unlinks a finished command from the archive's queue, publishes its result and wakes whoever was
 * waiting on it. */
void FSi_ReleaseCommand(char *file, int result) {
    int enabled = OS_DisableInterrupts();
    char *prev = *(char **)file;
    char *next = *(char **)(file + 4);
    if (prev != 0) {
        *(char **)(prev + 4) = next;
    }
    if (next != 0) {
        *(char **)next = prev;
    }
    *(char **)file = 0;
    *(char **)(file + 4) = 0;
    *(int *)(file + 0xc) &= ~0x4f;
    *(int *)(file + 0x14) = result;
    OS_WakeupThread(file + 0x18);
    OS_RestoreInterrupts(enabled);
}
