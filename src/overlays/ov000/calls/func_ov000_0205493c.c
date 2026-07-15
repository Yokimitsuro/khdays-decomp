#pragma thumb on
/* func_ov000_0205493c -- issue a save-backup WRITE command, ov000. Runs the CARD
 * backup transfer (func_0200e6d8, mode 8/0xa/2) and stashes its result code at
 * data_ov000_0205ac2c[+4]. */
extern void func_0200e6d8(void *, int, int, int, int, int, int, int, int);
extern int  CARD_GetResultCode(void);
extern char data_ov000_0205ac2c[];
void func_ov000_0205493c(int a, void *buf, int size) {
    func_0200e6d8(buf, a, size, 0, 0, 0, 8, 0xa, 2);
    *(int *)(data_ov000_0205ac2c + 4) = CARD_GetResultCode();
}
