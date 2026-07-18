extern int data_ov100_020bc1c0;
extern void func_ov100_020bb3d8(void);
extern void func_ov100_020bb1fc(void);

void *func_ov100_020bb0dc(int self, int a) {
    int base = *(int *)&data_ov100_020bc1c0 + 0xdf0 + 0x2000;
    void *cb = 0;
    if (a != 0x21) {
        if (a == 0x22) cb = (void *)&func_ov100_020bb3d8;
    } else {
        void (*fn)(int, int) = *(void (**)(int, int))(self + 0x664);
        if (*(int *)(base + 0x114) != 0) {
            fn(self, 0x30);
        } else {
            fn(self, 0x2f);
        }
        cb = (void *)&func_ov100_020bb1fc;
    }
    return cb;
}
