extern int func_ov107_020c08cc(int a, int b, int c, int d, int e, int f);
extern int func_ov107_020c7500(int a, int b, int c);

struct S {
    char pad0[2];
    unsigned char b2;
    unsigned char b3;
    char pad4[1];
    char data5[1];
};

struct R {
    char pad0[0x3c];
    int f3c;
    char pad40[0x390 - 0x40];
    int *f390;
};

int func_ov154_020d0420(struct R *r6, struct S *r5, int r4) {
    if (r5->b2 == 5) {
        switch (r5->b3) {
        case 0:
            r6->f390[1] = func_ov107_020c08cc(r6->f3c, r6->f390[0], 0x17, 0, 0x1000, (int)&r5->data5[0]);
            break;
        case 1:
            r6->f390[3] = func_ov107_020c08cc(r6->f3c, r6->f390[2], 0x17, 0, 0x1000, (int)&r5->data5[0]);
            break;
        }
    }
    return func_ov107_020c7500((int)r6, (int)r5, r4);
}
