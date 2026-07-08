typedef struct {
    char pad[0x3a0];
    void *data;
    int word0;
    int word1;
} Obj291;

typedef struct {
    int word0;
    int word1;
} Header291;

extern void MI_CpuCopy8(void *src, void *dst, int size);
extern void *func_0203d15c(int size);
extern void func_0203d194(void *ptr);

void func_ov291_020cc550(Obj291 *obj, int size, Header291 *src)
{
    void *dst;

    if (obj->data != 0) {
        func_0203d194(obj->data);
        obj->data = 0;
    }

    obj->data = func_0203d15c(size);
    MI_CpuCopy8(src, obj->data, size);
    obj->word0 = src->word0;
    obj->word1 = src->word1;
}
