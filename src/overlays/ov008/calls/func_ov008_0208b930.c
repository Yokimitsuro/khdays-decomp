extern int func_0200e6d8(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8);
extern int CARD_GetResultCode(void);
extern int data_ov008_02090fb4[];

void func_ov008_0208b930(int arg0, int arg1, int arg2)
{
    func_0200e6d8(arg0, arg1, arg2, 0, 0, 0, 6, 1, 0);
    data_ov008_02090fb4[1] = CARD_GetResultCode();
}
