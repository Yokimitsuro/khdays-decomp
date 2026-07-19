extern int func_02020904(void);
extern void func_ov025_020b094c(int arg0, int arg1, int arg2);

extern unsigned char data_ov025_020b5760[];
extern void *data_0204be14;

void func_ov025_020b0c40(int slot) {
    func_02020904();
    data_ov025_020b5760[0] = 0;
    data_ov025_020b5760[1] = (unsigned char)slot;
    func_ov025_020b094c((data_ov025_020b5760[1] << 1) * 0x2018 + 0x20,
                        (int)data_0204be14, 0x2018);
}
