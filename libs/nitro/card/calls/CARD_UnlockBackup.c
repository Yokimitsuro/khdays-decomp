/* CARD_UnlockBackup (NitroSDK): wait for the card's asynchronous request to end, then release
 * the backup held for lock id resource -- CARDi_UnlockResource(resource, CARD_TARGET_BACKUP = 2). */

extern int CARD_TryWaitRomAsync(void);
extern void CARD_WaitRomAsync(void);
extern void CARDi_UnlockResource(int resource, int kind);

void CARD_UnlockBackup(int resource) {
    if (CARD_TryWaitRomAsync() == 0)
        CARD_WaitRomAsync();
    CARDi_UnlockResource(resource, 2);
}
