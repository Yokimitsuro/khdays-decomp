extern void func_ov022_0209246c(int a, int b, void *c);

struct words3_020ad208 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

struct marshal_020ad208 {
    unsigned char b0;
    unsigned char pad1[3];
    struct words3_020ad208 w;
    short h10;
    short h12;
    unsigned char b14;
    unsigned char b13;
    unsigned char pad2[6];
};

void func_ov022_020ad208(int param_1, int param_2,
                         struct words3_020ad208 *param_3, int param_4,
                         unsigned int param_5, int param_6) {
    struct marshal_020ad208 buf;
    buf.b0 = *(unsigned char *)(param_1 + 9);
    buf.w = *param_3;
    buf.h10 = (short)param_4;
    buf.h12 = (short)param_5;
    if ((buf.b14 = (unsigned char)param_6, buf.b13 = 0, param_2) == 1) {
        if (*(unsigned char *)(param_1 + 0x26c4) == 1 &&
            (*(unsigned int *)(param_1 + 0x26bc) & 0x20) != 0) {
            buf.b13 |= 2;
        }
    }
    func_ov022_0209246c(param_1 + 0x2648, param_2, &buf);
}
