extern int func_02020904(void);
extern void func_ov009_02055a64(int arg0, int arg1, int arg2);

extern unsigned char data_ov009_020563f8[];
extern void *data_0204be14;

void func_ov009_02055d58(int slot) {
    func_02020904();
    data_ov009_020563f8[0] = 0;
    data_ov009_020563f8[1] = (unsigned char)slot;
    func_ov009_02055a64((data_ov009_020563f8[1] << 1) * 0x2018 + 0x20,
                        (int)data_0204be14, 0x2018);
}
