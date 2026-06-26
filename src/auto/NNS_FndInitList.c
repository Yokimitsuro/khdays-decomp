struct S {
    int a;
    int b;
    short c;
    short d;
};

void NNS_FndInitList(struct S *p, short val) {
    p->a = 0;
    p->b = 0;
    p->c = 0;
    p->d = val;
}
