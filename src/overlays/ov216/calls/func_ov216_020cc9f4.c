struct nine { int w[9]; };
struct b1 { unsigned char b : 1; };
extern int func_ov107_020c9440(void *this, int v);
extern void func_ov216_020cc97c(void *a, int b, int c, void *d);
extern void func_0203c7ac(void *a, int b);
extern int data_ov216_020cebf8[];

void func_ov216_020cc9f4(char *this) {
    int buf[9];
    int v;
    *(struct nine *)buf = *(struct nine *)data_ov216_020cebf8;
    v = func_ov107_020c9440(this, buf[*(signed char *)(this + 0x310)]);
    func_ov216_020cc97c(*(void **)(this + 0x384), v,
                        ((struct b1 *)(this + 0x311))->b, this + 0x388);
    func_0203c7ac(*(void **)(this + 0x384), 0);
}
