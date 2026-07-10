extern int func_02030694(void);
extern int func_02031384(int a, void *b, int c);

struct marshal_02091d80 {
    unsigned char f0 : 2;
    unsigned char f2 : 2;
    unsigned char f4 : 4;
    unsigned char g0 : 3;
    unsigned char g3 : 5;
    unsigned char b2;
};

void func_ov022_02091d80(unsigned int *param_1, int param_2, int param_3, int param_4) {
    int iVar2 = param_1[2];
    struct marshal_02091d80 m;
    if (func_02030694() != 0) {
        m.f0 = 1;
        m.f2 = *(unsigned char *)(iVar2 + 9);
        m.g0 = *param_1;
        m.b2 = *(char *)(param_2 + 1);
        func_02031384(9, &m, 3);
    }
}
