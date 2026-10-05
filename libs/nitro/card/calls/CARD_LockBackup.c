/* CARD_LockBackup (NitroSDK): take the card's backup for lock id id --
 * CARDi_LockResource(id, CARD_TARGET_BACKUP = 2). */
extern void *CARDi_LockResource();

void *CARD_LockBackup(int id) {
    return CARDi_LockResource(id, 2);
}
