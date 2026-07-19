extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern void OSi_DequeueItem(void *thread, void *mutex);
extern void OS_WakeupThread(void *queue);
extern char data_02044330;

/* Releases one level of a mutex; the last level hands it to the next waiting thread. */
void OS_UnlockMutex(char *mutex) {
    int enabled = OS_DisableInterrupts();
    char *self = *(char **)((char *)&data_02044330 + 4);
    if (*(char **)(mutex + 8) == self) {
        *(int *)(mutex + 0xc) = *(int *)(mutex + 0xc) - 1;
        if (*(int *)(mutex + 0xc) == 0) {
            OSi_DequeueItem(self, mutex);
            *(char **)(mutex + 8) = 0;
            OS_WakeupThread(mutex);
        }
    }
    OS_RestoreInterrupts(enabled);
}
