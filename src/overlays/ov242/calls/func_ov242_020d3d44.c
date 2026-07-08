typedef struct {
    int word0;
    int word1;
    int count;
    char data[0];
} Header242;

typedef struct {
    char pad[0x3a4];
    void *data;
    int count;
    char pad_3ac[8];
    int word0;
    int word1;
} Obj242;

extern void func_0203d194(void *ptr);
extern void *func_0203d15c(int size);
extern void MI_CpuCopy8(void *src, void *dst, int size);

void func_ov242_020d3d44(Obj242 *obj, int unused, Header242 *src)
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
