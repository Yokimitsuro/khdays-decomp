extern void MI_CpuFill8();
extern void NNS_FndInitList();
extern void *NNSi_FndAllocFromDefaultExpHeap();

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
    MI_CpuFill8(s, 0, 76);
    NNS_FndInitList(s, 44);
    s->field48 = b[0];
    s->field52 = b[1];
    s->field56 = b[2];
    s->field60 = b[3];
    s->field64 = b[4];
    s->field12 = NNSi_FndAllocFromDefaultExpHeap(56 * b[0]);
    s->field16 = NNSi_FndAllocFromDefaultExpHeap(48 * b[1]);
    s->field20 = NNSi_FndAllocFromDefaultExpHeap(16 * b[2]);
    MI_CpuFill8(s->field12, 0, 56 * b[0]);
    MI_CpuFill8(s->field16, 0, 48 * b[1]);
    MI_CpuFill8(s->field20, 0, 16 * b[2]);
}
