extern void func_01ff8830();
extern int *func_0201ef9c();

typedef struct {
    int *field0;
    int field4;
    int field8;
} Struct;

void func_ov000_02056938(void *a, int b) {
    Struct *s = (Struct *)a;
    int *p;
    int t;
    func_01ff8830(a, 0, 12);
    p = func_0201ef9c(b, 14);
    s->field0 = p;
    t = p[0];
    s->field4 = p[1];
    s->field8 = (int)s->field0 + t;
}
