/* Ov025_Backup_ReadChunked -- read the save block from backup memory, 0x80 bytes at a time: each
 * chunk is a CARD_ReadBackup (request 6, CARD_REQ_READ_BACKUP). The request is three fields on the
 * caller's context: the backup offset (+0x2c0), the remaining length (+0x2c4) and the destination
 * buffer (+0x2c8). Each chunk is read with the backup locked, and the thread is yielded between
 * chunks so a long read does not starve the rest of the frame. A failed chunk stops the loop and
 * records CARD's result code both in the shared status word (data_ov025_020b5760+4) and in the
 * context's own slot (+0x2cc); a clean run leaves that slot 0. THUMB -- the mov/lsl pairs building
 * 0x2c0 and 0x2cc are forced by the ISA, whose load offsets do not reach that far. */
extern void CARD_LockBackup(int lockId);
extern int CARDi_RequestStreamCommand(int src, int dst, int len, int a, int b, int c, int d, int e, int f);
extern int CARD_GetResultCode(void);
extern void CARD_UnlockBackup(int lockId);
extern void OS_RescheduleThread(void);
extern unsigned short data_0204be10;
extern int data_ov025_020b5760[];

void Ov025_Backup_ReadChunked(int ctx) {
    int src;
    int len;
    int dst;
    int chunk;
    int rc;

    src = *(int *)(ctx + 0x2c0);
    len = *(int *)(ctx + 0x2c4);
    dst = *(int *)(ctx + 0x2c8);

    do {
        if (len > 0x80) {
            chunk = 0x80;
        } else {
            chunk = len;
        }
        CARD_LockBackup(data_0204be10);
        if (CARDi_RequestStreamCommand(src, dst, chunk, 0, 0, 0, 6, 1, 0) == 0) {
            rc = CARD_GetResultCode();
            data_ov025_020b5760[1] = rc;
            *(int *)(ctx + 0x2cc) = rc;
            CARD_UnlockBackup(data_0204be10);
            return;
        }
        CARD_UnlockBackup(data_0204be10);
        src = src + chunk;
        dst = dst + chunk;
        len = len - chunk;
        OS_RescheduleThread();
    } while (len > 0);

    *(int *)(ctx + 0x2cc) = 0;
}
