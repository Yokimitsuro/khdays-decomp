extern int func_02020904(void);
extern void func_ov000_020549fc(int arg0, int arg1, int arg2);

extern unsigned char data_ov000_0205ac2c[];
extern void *data_0204be14;

void func_ov000_02054e48(int slot) {
    func_02020904();
    data_ov000_0205ac2c[0] = 0;
    data_ov000_0205ac2c[1] = (unsigned char)slot;
    func_ov000_020549fc((data_ov000_0205ac2c[1] << 1) * 0x2018 + 0x20,
                        (int)data_0204be14, 0x2018);
}
