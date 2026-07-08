typedef void (*Callback262)(void);

typedef struct {
    int unk0;
    Callback262 cb0;
    Callback262 cb1;
    Callback262 cb2;
    Callback262 cb3;
} Header262;

typedef struct {
    char pad[0x39c];
    void *aux;
    void *data;
} Obj262;

extern void func_0203d194(void *ptr);
extern void *func_0203d15c(int size);
extern void MI_CpuCopy8(void *src, void *dst, int size);
extern void func_ov262_020d3ec8(void);
extern void func_ov262_020d3ee8(void);
extern void func_ov262_020d3f08(void);
extern void func_ov262_020d3f28(void);

void func_ov262_020d3e4c(Obj262 *obj, int size, Header262 *src)
{
    if (obj->data != 0) {
        func_0203d194(obj->data);
        obj->data = 0;
        obj->aux = 0;
    }

    obj->data = func_0203d15c(size);
    MI_CpuCopy8(src, obj->data, size);
    src->cb0 = func_ov262_020d3ec8;
    src->cb1 = func_ov262_020d3ee8;
    src->cb2 = func_ov262_020d3f08;
    src->cb3 = func_ov262_020d3f28;
}
