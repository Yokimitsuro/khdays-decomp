extern int func_02030788(void);
extern void func_02031384(int arg0, void *arg1, int arg2);
extern int data_ov022_020b2ea4;

struct marshal_0208a134 {
    unsigned char pad[4];
    unsigned char b012 : 3;
    unsigned char b345 : 3;
    unsigned char b67 : 2;
    unsigned char pad5;
};

void func_ov022_0208a134(int param_1) {
    struct marshal_0208a134 m;
    if (data_ov022_020b2ea4 == 0) {
        return;
    }
    if (func_02030788() != 0) {
        return;
    }
    m.b345 = param_1;
    m.b012 = 2;
    func_02031384(0xf, &m, 6);
}
