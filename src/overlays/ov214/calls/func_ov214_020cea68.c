struct v3 { int x, y, z; };

extern void func_0202f188(void *a, void *b, int c);
extern long long func_02020400(int a, unsigned b);
extern int data_02042270[];

int func_ov214_020cea68(int *param_1, int *param_2) {
    int entry = *(int *)(*param_1 + 0x90) + param_1[1] * 0x38;
    long long r;
    *(int *)(*(int *)(*param_1 + 0x90) + param_1[1] * 0x38) = 0x1400;
    *(int *)(entry + 4) = 0x800;
    *(struct v3 *)(entry + 0x2c) = *(struct v3 *)param_2;
    func_0202f188((void *)(entry + 8), data_02042270, 0x1922);
    r = func_02020400(param_1[1] + 1, *(unsigned *)(*param_1 + 0x8c));
    param_1[1] = (int)(r >> 0x20);
    return (int)r;
}
