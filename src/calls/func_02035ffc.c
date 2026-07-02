extern long long func_020031d4(void);

struct obj {
    int _pad[4];
    long long value;
    unsigned flag0 : 1;
    unsigned flag1 : 1;
    unsigned flag2 : 1;
};

void func_02035ffc(struct obj *o) {
    o->value = func_020031d4();
    o->flag0 = 1;
    o->flag1 = 0;
    o->flag2 = 0;
}
