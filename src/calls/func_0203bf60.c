extern void func_0203c724(void *p);
extern void func_01fffc24(void *p);
extern void func_0203c054(void);
extern void func_0203c148(void);
extern void func_0203c17c(void);
extern void func_0203c070(void);
extern void func_0203c10c(void);

struct S {
    char _0[0x64];
    void (*x64)(void);
    void (*x68)(void);
    void (*x6c)(void);
    char _70[0x7c - 0x70];
    void (*x7c)(void);
    void (*x80)(void);
};

void func_0203bf60(struct S *p)
{
    func_0203c724(p);
    p->x64 = func_0203c054;
    p->x7c = func_0203c148;
    p->x80 = func_0203c17c;
    func_01fffc24((char *)p + 0x88);
    p->x68 = func_0203c070;
    p->x6c = func_0203c10c;
}
