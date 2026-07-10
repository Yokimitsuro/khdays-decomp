extern int func_ov022_0209405c(int arg0);
extern void func_01fff774(int arg0, int arg1, int arg2);

struct Vec3_020941a0 { int a, b, c; };

void func_ov022_020941a0(int arg0, int arg1) {
    if (func_ov022_0209405c(arg0)) {
        *(struct Vec3_020941a0 *)(arg0 + 0xa8) = *(struct Vec3_020941a0 *)arg1;
        func_01fff774(arg0 + 4, 0, 0);
        func_01fff774(arg0 + 4, 2, 0);
        func_01fff774(arg0 + 4, 3, 0);
        func_01fff774(arg0 + 4, 1, 0);
        if ((*(unsigned char *)arg0 & 0x10) == 0)
            *(int *)(arg0 + 0x10c) = *(int *)(arg0 + 0x118);
        *(unsigned char *)arg0 |= 0x20;
    }
}
