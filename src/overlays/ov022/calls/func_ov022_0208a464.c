extern int func_01fffe14(void);
extern void func_02031384(int a, void *buf, int c);

struct Buf0208a464 {
    unsigned short f0 : 3;
    unsigned short f3 : 2;
    unsigned short f5 : 5;
    unsigned short f10 : 3;
    unsigned short rest : 3;
};

void func_ov022_0208a464(int obj, int param_2, int *param_3) {
    int e = *(int *)(obj + 0x58);
    struct Buf0208a464 buf;
    buf.f0 = (unsigned short)func_01fffe14();
    buf.f3 = *(unsigned char *)(e + 9);
    buf.f10 = (unsigned short)param_2;
    if (param_2 == 0) buf.f5 = *param_3;
    func_02031384(0xc, &buf, 4);
}
