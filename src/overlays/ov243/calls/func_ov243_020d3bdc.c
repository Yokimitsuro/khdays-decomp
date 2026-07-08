typedef struct {
    int word0;
    int word1;
    int count;
    char data[0];
} Header243;

typedef struct {
    char pad[0x398];
    void *data;
    int count;
    char pad_3a0[8];
    int word0;
    int word1;
} Obj243;

extern void MI_CpuCopy8(void *src, void *dst, int size);
extern void *func_0203d15c(int size);
extern void func_0203d194(void *ptr);

void func_ov243_020d3bdc(Obj243 *obj, int unused, Header243 *src)
{
    if (obj->data != 0) {
        func_0203d194(obj->data);
        obj->data = 0;
    }

    obj->data = func_0203d15c(src->count * 0x14);
    MI_CpuCopy8(src->data, obj->data, src->count * 0x14);
    obj->count = src->count;
    obj->word0 = src->word0;
    obj->word1 = src->word1;
}
