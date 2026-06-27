extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int a, unsigned int b);
extern void func_02014148(void *a, void *b, int c, int d, int e);
extern void func_02030094(void *a, void *b, int c);
extern void MI_CpuFill8(void *dest, unsigned char value, unsigned int size);
extern void MIi_CpuClearFast(unsigned int data, void *destp, unsigned int size);
extern void NNS_FndAppendListObject(void *list, void *object);

typedef struct {
    int field_0;
    int field_4;
    int field_8;
    int field_c;
    char pad_10[0x38 - 0xc - 4];
    int field_38;
} S0202fff8;

void *func_0202fff8(S0202fff8 *a0, int a1)
{
    void *obj = NNSi_FndAllocFromDefaultExpHeap(0x24);
    void *buf;
    int mode;

    MI_CpuFill8(obj, 0, 0x24);
    buf = NNS_FndAllocFromDefaultExpHeapEx(a0->field_c, 0x20);
    *((void **)obj + 8) = buf;
    MIi_CpuClearFast(0, *((void **)obj + 8), a0->field_c);
    mode = a0->field_38 ? 8 : 4;
    func_02014148((char *)obj + 8, *((void **)obj + 8), a0->field_4, a0->field_8, mode);
    NNS_FndAppendListObject((char *)a0 + 0x2c, obj);
    if (a1 != 0) {
        func_02030094(a0, obj, 0);
    }
    return obj;
}
