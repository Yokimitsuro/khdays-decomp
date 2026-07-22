/* Same lookup as func_020358f4 but forwards a fourth argument and does not narrow the
 * result: reads packed parameter word `b` from data_0204c590 and passes its two bitfields,
 * plus (unsigned short)c, to func_02025754 together with the sub-record at +0x28 of
 * record `a` in data_0204c678. */
struct Params {
    unsigned short lo : 4;
    unsigned short hi : 12;
};

extern struct Params data_0204c590[];
extern unsigned char data_0204c678[];
extern int func_02025754(unsigned char *p, int hi, int lo, unsigned short d);

int func_020358c0(int a, int b, int c) {
    struct Params *v = &data_0204c590[b - 1];
    return func_02025754(data_0204c678 + a * 260 + 0x28, v->hi, v->lo, (unsigned short)c);
}
