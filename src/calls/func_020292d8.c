extern void func_0202926c(void *p, int a1, int a2, int a3);
extern char data_02042910[];

struct S { char _0[0x1c]; void *f_1c; char _20; unsigned char f_21; char _22[0x16]; int f_38; int f_3c; };

int func_020292d8(struct S *p, int arg1, int arg2, int arg3)
{
    func_0202926c(p, arg1, arg2, arg3);
    p->f_21 = 2;
    p->f_1c = data_02042910;
    p->f_38 = arg3;
    p->f_3c = arg3;
    return 1;
}
