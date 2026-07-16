/* func_ov000_0205496c -- write the pending save block to backup memory, 0x80 bytes at a time.
 * The request is three fields on the caller's context: source (+0x2c0), remaining length
 * (+0x2c4) and destination (+0x2c8). Each chunk is written with the backup unlocked, and the
 * thread is yielded between chunks so a long save does not starve the rest of the frame.
 * A failed chunk stops the loop and records CARD's result code both in the shared status word
 * (data_ov000_0205ac2c+4) and in the context's own slot (+0x2cc); a clean run leaves that slot 0.
 * THUMB -- the mov/lsl pairs building 0x2c0 and 0x2cc are forced by the ISA, whose load offsets
 * do not reach that far. */
extern void CARD_UnlockBackup(unsigned short lockId);
extern int func_0200e6d8(int src, int dst, int len, int a, int b, int c, int d, int e, int f);
extern int CARD_GetResultCode(void);
extern void func_0200e164(unsigned short lockId);
extern void OS_RescheduleThread(void);
extern unsigned short data_0204be10;
extern int data_ov000_0205ac2c[];

void func_ov000_0205496c(int ctx) {
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
        CARD_UnlockBackup(data_0204be10);
        if (func_0200e6d8(src, dst, chunk, 0, 0, 0, 6, 1, 0) == 0) {
            rc = CARD_GetResultCode();
            data_ov000_0205ac2c[1] = rc;
            *(int *)(ctx + 0x2cc) = rc;
            func_0200e164(data_0204be10);
            return;
        }
        func_0200e164(data_0204be10);
        src = src + chunk;
        dst = dst + chunk;
        len = len - chunk;
        OS_RescheduleThread();
    } while (len > 0);

    *(int *)(ctx + 0x2cc) = 0;
}
