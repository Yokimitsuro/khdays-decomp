struct S {
    int state;
    int a;
    int b;
    char pad[6];
    unsigned short flags;
};

void func_020122fc(struct S *p, int a, int b) {
    if (p->state != 1) return;
    p->flags |= 2;
    p->a = a;
    p->b = b;
}
