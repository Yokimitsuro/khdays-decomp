extern int func_02030788(void);
extern int func_02031384(int a, void *b, int c);
extern int data_ov022_020b2ea4;

struct marshal_0208a0b4 {
    unsigned short w;
    unsigned char b2;
    unsigned char pad3;
    unsigned char f012 : 3;
    unsigned char f345 : 3;
    unsigned char f67 : 2;
    unsigned char pad5;
};

void func_ov022_0208a0b4(int param_1, unsigned char param_2, unsigned short param_3) {
    struct marshal_0208a0b4 m;
    if (data_ov022_020b2ea4 == 0) {
        return;
    }
    if (func_02030788() != 0) {
        return;
    }
    m.w = param_3;
    m.b2 = param_2;
    m.f345 = param_1;
    m.f012 = 1;
    func_02031384(0xf, &m, 6);
}
