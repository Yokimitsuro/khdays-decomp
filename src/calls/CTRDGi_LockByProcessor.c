extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int OS_ReadOwnerOfLockWord(void *lock);
extern int OS_TryLockCartridge_0x02001730(int owner);
extern void WaitByLoop(int count);

/* Spins until this processor owns the cartridge bus. `out` receives the saved interrupt state and
 * the "already locked by the other CPU" flag. */
void CTRDGi_LockByProcessor(int owner, char *out) {
    for (;;) {
        *(int *)(out + 4) = OS_DisableInterrupts();
        *(int *)out = OS_ReadOwnerOfLockWord((void *)0x027fffe8) & 0x40;
        if (*(int *)out != 0) {
            return;
        }
        if (OS_TryLockCartridge_0x02001730(owner) == 0) {
            return;
        }
        OS_RestoreInterrupts(*(int *)(out + 4));
        WaitByLoop(1);
    }
}
