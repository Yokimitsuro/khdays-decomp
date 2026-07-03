struct v3 { int x, y, z; };

extern void func_0203bc78(int a, int b, int c, int d);
extern int func_02016320(int a, void *buf, void *c, unsigned d);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Mag(void *v);
extern void func_0203b9fc(int a, int b, int c, int d);
extern const struct v3 data_02041dc8;

void func_ov214_020cc09c(int param_1, int param_2, int param_3, int param_4) {
    int obj = *(int *)(param_1 + 0x84);
    int buf[12];
    struct v3 tmp;
    int t;
    func_0203bc78(param_1, param_2, param_3, param_4);
    if (func_02016320(*(int *)(param_1 + 0x88) + 0x20, buf, 0, *(unsigned *)(obj + 0x434)) != 0) {
        tmp = *(struct v3 *)&buf[9];
        VEC_Subtract(&tmp, (void *)(obj + 0x3b4), (void *)(obj + 0x424));
        *(struct v3 *)(obj + 0x3b4) = tmp;
        *(int *)(obj + 0x430) = VEC_Mag((void *)(obj + 0x424));
    }
    if (*(unsigned char *)(param_1 + 0xad) != 0) return;
    t = *(short *)(*(int *)(param_1 + 0x88) + 2);
    switch (t) {
    case 1:
    case 2:
        func_0203b9fc(param_1, 0, (short)(t + 1), 0);
        return;
    case 3:
        {
            struct v3 stage = data_02041dc8;
            *(int *)(obj + 0x430) = 0;
            *(struct v3 *)(obj + 0x3b4) = stage;
            *(struct v3 *)(obj + 0x424) = stage;
        }
        return;
    default:
        if (t >= 0) func_0203b9fc(param_1, 0, t, 0);
        {
            struct v3 stage = data_02041dc8;
            *(int *)(obj + 0x430) = 0;
            *(struct v3 *)(obj + 0x3b4) = stage;
            *(struct v3 *)(obj + 0x424) = stage;
        }
    }
}
