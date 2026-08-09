extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_02001f10(void *queue);
extern int FSi_ExecuteSyncCommand(void *file);

static inline int FSi_IsBusy(char *file) {
    return (*(volatile int *)(file + 0xc) & 1) != 0;
}

static inline int FSi_IsSucceeded(char *file) {
    return *(int *)(file + 0x14) == 0;
}

/* Blocks until the file's pending command has finished. If nobody else is already waiting we take
 * ownership and run the command synchronously ourselves. */
int FS_WaitAsync(char *file) {
    int owner = 0;
    int enabled = OS_DisableInterrupts();
    if (FSi_IsBusy(file)) {
        owner = (*(volatile int *)(file + 0xc) & 0x44) == 0;
        if (owner != 0) {
            *(volatile int *)(file + 0xc) |= 4;
            do {
                func_02001f10(file + 0x18);
            } while ((*(volatile int *)(file + 0xc) & 0x40) == 0);
        } else {
            do {
                func_02001f10(file + 0x18);
            } while (FSi_IsBusy(file));
        }
    }
    OS_RestoreInterrupts(enabled);
    if (owner != 0) {
        return FSi_ExecuteSyncCommand(file);
    }
    return FSi_IsSucceeded(file);
}
