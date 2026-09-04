extern void WaitByLoop(unsigned count);
extern int OSi_DoTryLockByWord(unsigned short id, char *lock, void (*onLock)(void), int fiq);

/* Blocks until the lock word is ours, retrying the non-blocking attempt with a short
 * spin in between. A positive result means somebody else still owns it; zero means we
 * took it and a negative value is an error the caller has to see, so both fall out of
 * the loop and are returned unchanged. */
int OSi_DoLockByWord(unsigned short id, char *lock, void (*onLock)(void), int fiq) {
    int prev = OSi_DoTryLockByWord(id, lock, onLock, fiq);

    while (prev > 0) {
        WaitByLoop(0x400);
        prev = OSi_DoTryLockByWord(id, lock, onLock, fiq);
    }
    return prev;
}
