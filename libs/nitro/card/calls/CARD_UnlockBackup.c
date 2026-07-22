/* Releases the backup lock: CARDi_LockResource(id, 2). */
extern void *CARDi_LockResource();

void *CARD_UnlockBackup(int id) {
    return CARDi_LockResource(id, 2);
}
