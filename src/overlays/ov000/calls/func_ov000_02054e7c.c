/* Save file layout, confirmed against the write side (func_ov008_0208bd9c):
 *   +0x00  magic 0xc8f592a6
 *   +0x04  SHA1 digest (0x14 bytes)
 *   +0x18  payload, 0x1cac bytes -- this IS the game state, and its +0x10 is the
 *          packed flag/bitfield store that GameState_IsFlagSet reads.
 * Block size on the card is 0x2018. */
typedef struct {
    unsigned char blockCounter;
    unsigned char slot;
    unsigned char pad02[2];
    int resultCode;
    void *thread;
} CardTransferCtx;

extern int func_ov000_02054a50(void);
extern int func_ov000_02054a84(void *buf);
extern void func_ov000_020549fc(int a, int b, int c);
extern int func_020208f0(void);

extern char *data_0204be14;
extern char *data_0204be18;
extern CardTransferCtx data_ov000_0205ac2c;

int func_ov000_02054e7c(void) {
    int ret;
    int status;
    int *word;
    unsigned int i;

    status = func_ov000_02054a50();
    if (status < 0) {
        goto out_busy;
    }
    if (status != 0) {
        ret = 3;
    } else {
        word = (int *)data_0204be14;
        for (i = 0; i < 8; i++) {
            if (*word++ != 0) {
                break;
            }
        }
        if (i == 8) {
            ret = 2;
        } else if (func_ov000_02054a84(data_0204be14) != 0) {
            ret = 0;
            data_0204be18 = data_0204be14 + 0x18;
        } else {
            data_ov000_0205ac2c.blockCounter = data_ov000_0205ac2c.blockCounter + 1;
            if (data_ov000_0205ac2c.blockCounter >= 2) {
                ret = 4;
            } else {
                func_ov000_020549fc(
                    (data_ov000_0205ac2c.blockCounter
                     + data_ov000_0205ac2c.slot * 2) * 0x2018 + 0x20,
                    (int)data_0204be14, 0x2018);
                return 1;
            }
        }
    }
    goto out_tail;
out_busy:
    return 1;
out_tail:
    func_020208f0();
    return ret;
}
