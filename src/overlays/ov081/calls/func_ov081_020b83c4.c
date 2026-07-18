extern void func_ov081_020b9238();
extern void func_ov022_020a384c();

void func_ov081_020b83c4(int self, int a) {
    int base = self + 0x2c;
    switch (a) {
    case 0x2f:
    case 0x30:
        if (a != *(int *)(self + 0x6bc)) func_ov081_020b9238(self, base + 0x2c00);
        break;
    }
    func_ov022_020a384c(self, a);
}
