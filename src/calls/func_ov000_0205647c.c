extern void func_01ff8830();
extern void func_0200ff7c();
extern void *func_02023660();

typedef struct {
    int field0;
    int field4;
    int field8;
    void *field12;
    void *field16;
    void *field20;
    int pad24[6];
    int field48;
    int field52;
    int field56;
    int field60;
    int field64;
} Struct;

void func_ov000_0205647c(void *a, int *b) {
    Struct *s = (Struct *)a;
    func_01ff8830(s, 0, 76);
    func_0200ff7c(s, 44);
    s->field48 = b[0];
    s->field52 = b[1];
    s->field56 = b[2];
    s->field60 = b[3];
    s->field64 = b[4];
    s->field12 = func_02023660(56 * b[0]);
    s->field16 = func_02023660(48 * b[1]);
    s->field20 = func_02023660(16 * b[2]);
    func_01ff8830(s->field12, 0, 56 * b[0]);
    func_01ff8830(s->field16, 0, 48 * b[1]);
    func_01ff8830(s->field20, 0, 16 * b[2]);
}
