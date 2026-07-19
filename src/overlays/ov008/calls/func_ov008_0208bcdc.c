extern int func_02020904(void);
extern void func_ov008_0208b9e8(int arg0, int arg1, int arg2);

extern unsigned char data_ov008_02090fb4[];
extern void *data_0204be14;

void func_ov008_0208bcdc(int slot) {
    func_02020904();
    data_ov008_02090fb4[0] = 0;
    data_ov008_02090fb4[1] = (unsigned char)slot;
    func_ov008_0208b9e8((data_ov008_02090fb4[1] << 1) * 0x2018 + 0x20,
                        (int)data_0204be14, 0x2018);
}
