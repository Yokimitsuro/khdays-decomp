extern int func_ov107_020cab14();
extern int func_01ff8bc4();
extern int func_01ff8d18();
extern int func_020050b4();

struct s3 {
    int a;
    int b;
    int c;
};

int func_ov227_020d14bc(int *arg0, struct s3 *out) {
    int **r4;
    int *r3;
    int r6;
    struct s3 v;

    r4 = (int **)arg0[1];
    r3 = (int *)(*r4)[250];
    if (r3 == 0) {
        (*r4)[250] = func_ov107_020cab14(*r4, 0);
        r3 = (int *)(*r4)[250];
        if (r3 == 0) {
            *((char *)*r4 + 0x1c7) = 2;
            return -1;
        }
    }

    func_01ff8bc4((int)r3 + 0x190, r4[2], &v);
    v.b = 0;
    r6 = func_01ff8d18(&v, &v, 0);
    r6 = r6 - (((int *)(*r4)[250])[32] + (*r4)[32]);
    if (r6 < 0) {
        r6 = 0;
    }
    ((int *)r4)[22] = func_020050b4(v.a, v.c);
    if (out != 0) {
        *out = v;
    }
    return r6;
}
