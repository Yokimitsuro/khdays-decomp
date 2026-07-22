/* Unlock half of the lock-word pair: OSi_DoLockByWord(id, word, callback, 0). */
extern void *OSi_DoLockByWord();

void *OS_UnlockByWord(int id, void *word, void *callback) {
    return OSi_DoLockByWord(id, word, callback, 0);
}
