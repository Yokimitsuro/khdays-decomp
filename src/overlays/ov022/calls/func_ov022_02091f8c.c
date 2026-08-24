extern unsigned int *func_01fffde0(int kind);
extern void func_ov022_020922a4(unsigned int *base, int obj, int a, int b);
extern int func_01fffe14(void);
extern int func_ov022_02088474(int state);
extern int func_02020a9c(void);
extern void func_ov106_020b8140(int obj);
extern void func_ov002_02061df8(int obj);
extern void func_ov022_02092060(unsigned int *base, int value, int obj);

struct Ctl02091f8c {
    unsigned int kind : 2;
    unsigned int _pad02 : 3;
    unsigned int selector : 4;
    unsigned int _pad09 : 2;
    unsigned int valueA : 12;
    unsigned int valueB : 8;
    unsigned int _pad31 : 1;
};

void func_ov022_02091f8c(int obj) {
    struct Ctl02091f8c *control =
        (struct Ctl02091f8c *)(obj + 0x10);
    unsigned int *base = func_01fffde0(control->kind);
    int raw = *(int *)control;
    unsigned int *table = base + 0x992;
    int state;

    switch (control->selector) {
    case 6:
        func_ov022_020922a4(base, obj, control->valueA, control->valueB);
        return;
    case 7:
        state = func_ov022_02088474(func_01fffe14());
        if (state != func_ov022_02088474(*((unsigned char *)base + 9))) {
            return;
        }
        if (func_02020a9c() == 0x2a) {
            func_ov106_020b8140(obj);
        } else {
            func_ov002_02061df8(obj);
        }
        return;
    case 8:
        if (table[1] == 0) {
            return;
        }
        func_ov022_02092060(base, table[1], obj);
        return;
    }

    if (table[control->selector] == 0) {
        return;
    }
    func_ov022_02092060(base, table[control->selector], obj);
}
