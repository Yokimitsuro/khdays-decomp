/* Snapshot the +0x64 vector, decay the +0x68 timer; once it goes negative and ready, dispatch. */
extern int func_0203c634(int, int, void *);
struct w3 { int a, b, c; };
struct bit0 { unsigned char b : 1; };
extern int func_ov118_020d11d4(int);
void func_ov118_020d1698(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(struct w3 *)(owner + 0x2c) = *(struct w3 *)(owner + 0x64);
    int delta = *(int *)(*(int *)param_1 + 0x2c);
    int r = *(int *)(owner + 0x68) - (int)((((long long)(delta * 30) << 7) + 0x800) >> 12);
    *(int *)(owner + 0x68) = r;
    if (r >= 0) return;
    if ((((struct bit0 *)(*(int *)owner + 0x17a))->b) == 0) return;
    *(int *)(owner + 0x38) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov118_020d11d4);
}
