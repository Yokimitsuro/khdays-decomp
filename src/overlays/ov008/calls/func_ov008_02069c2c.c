extern void func_ov008_02050cd4(void);
extern void func_ov008_02050c54(void);
extern void func_ov008_02069bec(int arg0, int arg1);
extern char data_ov008_020905a0[];

void func_ov008_02069c2c(int arg0, int index, int column)
{
    func_ov008_02050cd4();
    func_ov008_02050c54();
    func_ov008_02069bec(arg0, *(short *)(data_ov008_020905a0 + (short)index * 0x14 + column * 4));
}
