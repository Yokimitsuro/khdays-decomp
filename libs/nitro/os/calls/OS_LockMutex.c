extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OSi_EnqueueTail(void *thread, void *mutex);
extern void func_02001f10(void *queue);
extern char data_02044330;

/* Takes a mutex, blocking on its wait queue until the current owner releases it. Recursive locks
 * just bump the count. */
void OS_LockMutex(char *mutex) {
    int enabled = OS_DisableInterrupts();
    char *self = *(char **)((char *)&data_02044330 + 4);
    char *none = 0;
    char *owner;
    for (;;) {
        owner = *(char **)(mutex + 8);
        if (owner == 0) {
            *(char **)(mutex + 8) = self;
            *(int *)(mutex + 0xc) = *(int *)(mutex + 0xc) + 1;
            OSi_EnqueueTail(self, mutex);
            break;
        }
        if (owner == self) {
            *(int *)(mutex + 0xc) = *(int *)(mutex + 0xc) + 1;
            break;
        }
        *(char **)(self + 0x84) = mutex;
        func_02001f10(mutex);
        *(char **)(self + 0x84) = none;
    }
    OS_RestoreInterrupts(enabled);
}
