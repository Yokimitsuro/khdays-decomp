extern int func_01ff8d18();
extern int func_0202ed60();
extern int func_0203c9d0();

struct s3 {
    int a;
    int b;
    int c;
};

extern struct s3 data_02042264;

void func_ov170_020cdde4(int unused, char *obj) {
    struct s3 v10;
    char s0[16];

    if (func_01ff8d18(obj + 0xcc, &v10) < 8) {
        v10 = data_02042264;
    }
    func_0202ed60(s0, &data_02042264, &v10);
    func_0203c9d0(*(int *)(obj + 0x390) + 4, s0);
}
