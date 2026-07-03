extern void *func_ov107_020cab14(void *obj, int a);
extern void func_0203c634(void *node, int idx, void *value);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *v, void *v2);
extern int func_020050b4(int a, int b);
extern int VEC_DotProduct(void *a, void *b);
extern void func_01ffa724(int scale, void *vec, void *out);
extern void func_ov107_020c9264(void *obj, int a, int b);
extern void func_ov161_020cda7c(void);

extern short data_0203d210[];

void func_ov161_020cd8d4(int *node)
{
    int vd[3];
    int va[3];
    int *state = (int *)node[1];
    int *obj;
    int dist;
    int angle;
    short *tbl;

    state[2] = (int)func_ov107_020cab14((void *)*state, 0);
    if (state[2] == 0) {
        obj = (int *)*state;
        *((signed char *)obj + 0x1c7) = 2;
        func_0203c634(node, (signed char)*((char *)node + 0x20), 0);
        return;
    }

    VEC_Subtract((char *)state[2] + 0x190, (char *)*state + 0xb0, vd);
    vd[1] = 0;

    {
        int *o = (int *)*state;
        int *h = (int *)state[2];
        dist = func_01ff8d18(vd, vd) - (*(int *)((char *)h + 0x80) + *(int *)((char *)o + 0x80));
    }
    state[4] = func_020050b4(vd[0], vd[2]);

    angle = (int)(((unsigned)(((long long)state[3] * 0x28be60db9391LL + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;

    va[1] = 0;
    tbl = data_0203d210;
    va[0] = tbl[angle * 2];
    va[2] = tbl[angle * 2 + 1];

    {
        int dot = VEC_DotProduct(va, vd);
        if (dot < 0)
            dot = -dot;
        func_01ffa724((int)(((long long)dot * 0x300 + 0x800) >> 0xc), va, state + 6);
    }

    obj = (int *)*state;
    if (dist >= *(int *)((char *)obj + 0x2d8)) {
        *((signed char *)obj + 0x1c7) = 2;
        func_0203c634(node, (signed char)*((char *)node + 0x20), 0);
        return;
    }
    if (dist > 0x1000)
        return;
    func_ov107_020c9264(obj, 9, 0);
    func_0203c634(node, (signed char)*((char *)node + 0x20), func_ov161_020cda7c);
}
