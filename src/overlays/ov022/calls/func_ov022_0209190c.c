extern int func_02031384(int a, void *b, int c);

struct marshal_0209190c {
    unsigned char b0_1 : 2;
    unsigned char b2_3 : 2;
    unsigned char b4_6 : 3;
    unsigned char b7 : 1;
    unsigned char c0_2 : 3;
    unsigned char c3_7 : 5;
};

void func_ov022_0209190c(unsigned int *param_1, int param_2, int param_3, unsigned int param_4) {
    struct marshal_0209190c m;
    m.b0_1 = 2;
    m.b2_3 = *(unsigned char *)(param_1[2] + 9);
    m.b4_6 = *(short *)(param_1[2] + 0x66);
    m.c0_2 = *param_1;
    func_02031384(9, &m, 2);
}
