/* Snapshot +0x30, decay +0x34, tick the +0x3c dwell; once armed and ready, dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
struct w3 { int a, b, c; };
struct bit0 { unsigned char b : 1; };
extern int func_ov158_020cd50c(int);
void func_ov158_020cd450(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(struct w3 *)(owner + 0x18) = *(struct w3 *)(owner + 0x30);
    int delta = *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(owner + 0x34) -= (int)((((long long)(delta * 30) << 7) + 0x800) >> 12);
    *(int *)(owner + 0x3c) += 1;
    int obj = *(int *)owner;
    if (*(int *)(obj + 0x10c) >= 0) {
        if (*(int *)(owner + 0x3c) <= 4) return;
        if ((((struct bit0 *)(obj + 0x17a))->b) == 0) return;
    }
    func_ov107_020c9264(obj, 3, 1);
    *(int *)(owner + 0x3c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov158_020cd50c);
}
