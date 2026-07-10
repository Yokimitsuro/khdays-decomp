extern int func_01fffe14(void);
extern int func_02031384(int arg0, void *arg1, int arg2);

struct marshal_02094730 {
    unsigned char f0 : 2;
    unsigned char f2 : 3;
    unsigned char f5 : 3;
};

void func_ov022_02094730(int param_1, int param_2) {
    struct marshal_02094730 m;
    m.f0 = *(unsigned char *)(*(int *)(param_1 + 0x328) + 9);
    m.f2 = func_01fffe14();
    m.f5 = param_2;
    *(short *)(param_1 + 0x33c) = func_02031384(0x10, &m, 1);
}
