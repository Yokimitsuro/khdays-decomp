#pragma thumb on
/* func_ov000_02054914 -- issue a save-backup READ command, ov000. Runs the CARD
 * backup transfer (func_0200e6d8, mode 6/1) and stashes its result code at
 * data_ov000_0205ac2c[+4]. */
extern void func_0200e6d8(int, void *, int, int, int, int, int, int, int);
extern int  CARD_GetResultCode(void);
extern char data_ov000_0205ac2c[];
void func_ov000_02054914(int a, void *buf, int size) {
    func_0200e6d8(a, buf, size, 0, 0, 0, 6, 1, 0);
    *(int *)(data_ov000_0205ac2c + 4) = CARD_GetResultCode();
}
