extern void func_0200e6d8();
extern int CARD_GetResultCode();
extern int data_ov025_020b5760;

void func_ov025_020b0894(unsigned int arg0, unsigned int arg1, unsigned int arg2) {
    func_0200e6d8(arg0, arg1, arg2, 0, 0, 0, 6, 1, 0);
    *(int *)((char *)&data_ov025_020b5760 + 4) = CARD_GetResultCode();
}
