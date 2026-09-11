typedef struct ResGroup ResGroup;

extern void func_0202552c(ResGroup *state);
extern void func_020163f4(void *pResData);
extern int func_02023728(int resGroup, int *heap);

struct S {
    unsigned short field_00;
    unsigned short field_02;
    unsigned short field_04;
    unsigned short field_06;
    int *field_08;
    ResGroup *field_0c;
    unsigned char field_10;
};

int func_0201f5ac(struct S *p)
{
    p->field_00 = p->field_00 - 1;
    if (p->field_00 == 0) {
        if (p->field_02 != 0) {
            if (*(int *)p->field_0c == 0x4850414B) {
                func_0202552c(p->field_0c);
            } else {
                func_020163f4(p->field_0c);
            }
            p->field_02 = 0;
            p->field_04 = 0;
        }
        p->field_10 = 0;
        func_02023728((int)p->field_0c, p->field_08);
        p->field_0c = 0;
        return 1;
    }
    return 0;
}
