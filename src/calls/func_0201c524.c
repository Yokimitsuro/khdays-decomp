typedef unsigned char u8;
typedef unsigned short u16;

extern int OS_IsThreadAvailable_0x0201b3d8(void);
extern int func_0201b5dc(unsigned int idx);
extern void func_02019dd0(int index, int value);
extern void func_02019df0(int index, int value);
extern void *func_02019e08(int a0, void *a1, unsigned int a2);

typedef struct Entry {
    u8  byte0;
    u8  pad_01;
    u16 field_02;
    int field_04;
} Entry;

int func_0201c524(void *a0)
{
    int i;
    Entry *p;
    int j;

    OS_IsThreadAvailable_0x0201b3d8();
    for (i = 0; i < 0x20; i++) {
        p = (Entry *)func_0201b5dc(i);
        if (p == 0) continue;
        func_02019dd0(i, p->byte0);
        func_02019df0(i, p->field_02);
        if (p->field_04 != 0 && a0 != 0) {
            for (j = 0; j < p->byte0; j++) {
                if (func_02019e08(i, a0, p->field_04) == 0) return 0;
            }
        }
    }
    return 1;
}
