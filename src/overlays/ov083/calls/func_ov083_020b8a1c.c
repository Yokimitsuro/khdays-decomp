extern int data_ov083_020b9b00;
extern void func_ov083_020b8d18(void);
extern void func_ov083_020b8b3c(void);

void *func_ov083_020b8a1c(int self, int a) {
    int base = *(int *)&data_ov083_020b9b00 + 0xdf0 + 0x2000;
    void *cb = 0;
    if (a != 0x21) {
        if (a == 0x22) cb = (void *)&func_ov083_020b8d18;
    } else {
        void (*fn)(int, int) = *(void (**)(int, int))(self + 0x664);
        if (*(int *)(base + 0x114) != 0) {
            fn(self, 0x30);
        } else {
            fn(self, 0x2f);
        }
        cb = (void *)&func_ov083_020b8b3c;
    }
    return cb;
}
