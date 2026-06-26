extern int func_020236ac();

struct S {
    char pad[0x3c];
    int f3c;
    int f40;
    int f44;
    int f48;
};

void func_ov302_020cc0ac(struct S *p)
{
    if (p->f3c) {
        func_020236ac();
        p->f3c = 0;
    }
    if (p->f40) {
        func_020236ac();
        p->f40 = 0;
    }
    if (p->f44) {
        func_020236ac();
        p->f44 = 0;
    }
    if (p->f48) {
        func_020236ac();
        p->f48 = 0;
    }
}
