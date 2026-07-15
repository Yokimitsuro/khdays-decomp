#pragma thumb on
/* func_ov009_020559ac -- issue a save-backup READ command, ov009 (byte-identical twin of an ov000 helper). Runs the CARD
 * backup transfer (func_0200e6d8, mode 6/1) and stashes its result code at
 * data_ov009_020563f8[+4]. */
extern void func_0200e6d8(int, void *, int, int, int, int, int, int, int);
extern int  CARD_GetResultCode(void);
extern char data_ov009_020563f8[];
void func_ov009_020559ac(int a, void *buf, int size) {
    func_0200e6d8(a, buf, size, 0, 0, 0, 6, 1, 0);
    *(int *)(data_ov009_020563f8 + 4) = CARD_GetResultCode();
}
