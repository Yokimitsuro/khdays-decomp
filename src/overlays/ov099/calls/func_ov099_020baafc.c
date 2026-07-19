extern int func_02023588(int a);
extern int func_02024ee8(void *a, int b);
extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov002_02051d6c(int a, int b, int c);
extern void func_ov002_02051eec(int a, int b, int c, int d, int e);
extern void func_02024fd4(int a);
extern int data_ov099_020bcbc0;
extern unsigned char data_0204c240;
extern int data_ov099_020bcb1c;

void func_ov099_020baafc(int self) {
    int base = *(int *)&data_ov099_020bcbc0;
    int obj = *(int *)(self + 0x2bd0);
    int ok = 1;
    if ((data_0204c240 & 4) == 0 && func_02023588(0x208c) != 0) {
        ok = 0;
    }
    *(int *)(self + 0x2bd0) = func_02024ee8(&data_ov099_020bcb1c, 6);
    if (ok != 0) {
        func_ov022_0209fb60(base, 1, 2);
        if (*(signed char *)(base + 0xf0d) != 0) {
            *(unsigned char *)(base + 0xf0c) |= 1;
        }
        func_ov002_02051d6c(base + 0xf0c, base + 0x2c54, self + 0x910);
        func_ov002_02051eec(self + 0xf0c, base + 0x2c54, obj,
                            *(unsigned char *)(self + 9), 0x78);
    }
    func_02024fd4(obj);
}
