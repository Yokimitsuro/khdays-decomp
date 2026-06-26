extern int func_02014b5c();
extern int func_0202a388();
extern int func_0202a440();
extern int func_0203b9ac();
extern int func_0203b9fc();

struct B {
    char pad[0x78];
    int f78;
};

struct A {
    char pad[0x88];
    struct B *b;
};

int func_ov206_020cc85c(struct A *a, int b, int c, int *d)
{
    struct B *p;

    func_0202a440(d);
    d[3] = 0;
    p = a->b;
    func_02014b5c((char *)p + 0x20, p->f78);
    func_0202a388(d, p, b, 0xc);
    func_0203b9ac(a, d);
    return func_0203b9fc(a, 0, 0, c);
}
