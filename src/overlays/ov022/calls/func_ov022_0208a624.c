extern int func_01fffe14(void);
extern int func_02031384(int a, void *b, int c);

union marshal_0208a624 {
    unsigned int raw;
    struct {
        unsigned short f0 : 3;
        unsigned short f3 : 2;
        unsigned short f5 : 5;
        unsigned short f10 : 3;
        unsigned short f13 : 3;
        unsigned short high;
    } f;
};

void func_ov022_0208a624(int param_1, int param_2, int param_3, int param_4) {
    int iVar3 = *(int *)(param_1 + 0x58);
    union marshal_0208a624 m;
    m.f.f0 = func_01fffe14();
    m.f.f3 = *(unsigned char *)(iVar3 + 9);
    m.f.f10 = 3;
    m.f.f5 = *(int *)(iVar3 + 0x6bc);
    *(short *)(param_1 + 0x6c) = func_02031384(0xc, &m, 4);
}
