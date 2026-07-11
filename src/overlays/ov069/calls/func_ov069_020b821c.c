extern int func_02023588(int i);
extern void func_ov002_0206e700(int a, int count);

int func_ov069_020b821c(unsigned int arg) {
    int count = 0;
    int i;
    for (i = 9; i < 0x409; i++) {
        if (func_02023588(i)) count++;
    }
    func_ov002_0206e700(1, count);
    if ((unsigned int)count < arg) return 0;
    return 1;
}
