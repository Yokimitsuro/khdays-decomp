extern void INITi_CpuClear32_0x01ff86fc(unsigned int data, void *dst, unsigned int size);

extern int data_020424a8;
extern int data_020424ac;
extern int data_020424b0;

struct S {
    int _0;
    int field_4;
    int _8;
    int field_c;
    int _10;
    int field_14;
    int _18;
    int field_1c;
};

void func_02014b5c(struct S *p, int arg1) {
    INITi_CpuClear32_0x01ff86fc(0, p, 0x54);
    p->field_c = data_020424b0;
    p->field_14 = data_020424ac;
    p->field_1c = data_020424a8;
    p->field_4 = arg1;
}
