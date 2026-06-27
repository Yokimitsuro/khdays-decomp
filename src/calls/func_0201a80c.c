extern int NNS_FndAppendListObject();
extern int NNS_FndRemoveListObject();
extern int data_0204a314;
extern int data_0204a308;

typedef struct S {
    int *f0;
    struct S *f4;
    struct S *f8;
    char pad[0x20];
    char f2c;
} S;

void func_0201a80c(S *a) {
    S *r5;
    int *p;

    p = a->f0;
    if (p) {
        *p = 0;
        a->f0 = 0;
    }
    r5 = a->f4;
    NNS_FndRemoveListObject(r5, a);
    a->f4 = 0;
    if (a->f8) {
        NNS_FndAppendListObject((char *)r5 + 0xc, a->f8);
        *(int *)((char *)a->f8 + 0xc) = 0;
        a->f8 = 0;
    }
    NNS_FndRemoveListObject(&data_0204a314, a);
    NNS_FndAppendListObject(&data_0204a308, a);
    a->f2c = 0;
}
