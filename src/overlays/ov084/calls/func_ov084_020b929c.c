extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

typedef struct { int x, y, z; } Vec3;

void func_ov084_020b929c(char *arr, Vec3 *src) {
    char *slot = 0;
    int i;
    char *q = arr + 0x128;
    for (i = 0; i < 6; i++, arr += 0x120, q += 0x120) {
        if (*(int *)(arr + 0x128) == 0) slot = q;
    }
    if (slot == 0) return;
    *(int *)slot = 1;
    *(int *)(slot + 0x10c) = 0;
    func_0202accc((int)(slot + 4), 0, (int)(slot + 0xe4), 0);
    func_0202accc((int)(slot + 4), 2, (int)(slot + 0xe4), 0);
    func_01fff774((int)(slot + 4), 0, 0);
    func_01fff774((int)(slot + 4), 0, 0);
    *(Vec3 *)(slot + 0xa8) = *src;
}
