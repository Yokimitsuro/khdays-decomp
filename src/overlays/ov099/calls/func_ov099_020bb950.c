extern int func_01fff774(int, int, int);
extern int func_0202aee0(int, int);

void func_ov099_020bb950(int r0) {
    int r4 = r0;
    int r1 = *(int *)(r4 + 0xdb4);
    int v = *(int *)(r1 + 0x6bc);
    int n;

    if (v != 0x2f && v != 0x30) {
        if (*(int *)(r4 + 0x124) != 0) {
            *(int *)(r4 + 0x124) = 0;
        }
    }

    if (*(int *)(r4 + 0x124) != 1) {
        return;
    }

    n = func_0202aee0(*(int *)(r1 + 0x20) + 4, 0);
    if (n <= 0x1000) {
        return;
    }

    func_01fff774(r4 + 0x128, 0, n - 0x1000);
    func_01fff774(r4 + 0x128, 2, n - 0x1000);
    func_01fff774(r4 + 0x128, 1, n - 0x1000);
}
