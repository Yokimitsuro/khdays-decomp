extern int func_02016b60();
extern int func_0202aa9c();

struct S {
    char pad[0x78];
    int *p78;
    char pad2[0x12c - 0x7c];
    unsigned char b12c;
    unsigned char b12d;
};

void func_ov030_020b43c0(struct S *r4) {
    switch (r4->b12c) {
    case 2:
    case 3:
    case 4:
    case 5:
        func_02016b60(r4->p78, 5, 0x1c - r4->b12d);
        func_0202aa9c(r4);
        return;
    case 0:
    case 1:
    default:
        return;
    }
}
