typedef void (*Callback261)(void);

typedef struct {
    int unk0;
    Callback261 cb0;
    Callback261 cb1;
    Callback261 cb2;
    Callback261 cb3;
} Header261;

typedef struct {
    char pad[0x39c];
    void *aux;
    void *data;
} Obj261;

extern void func_0203d194(void *ptr);
extern void *func_0203d15c(int size);
extern void MI_CpuCopy8(void *src, void *dst, int size);
extern void func_ov261_020d0288(void);
extern void func_ov261_020d02a8(void);
extern void func_ov261_020d02c8(void);
extern void func_ov261_020d02e8(void);

void func_ov261_020d020c(Obj261 *obj, int size, Header261 *src)
{
    if (obj->data != 0) {
        func_0203d194(obj->data);
        obj->data = 0;
        obj->aux = 0;
    }

    obj->data = func_0203d15c(size);
    MI_CpuCopy8(src, obj->data, size);
    src->cb0 = func_ov261_020d0288;
    src->cb1 = func_ov261_020d02a8;
    src->cb2 = func_ov261_020d02c8;
    src->cb3 = func_ov261_020d02e8;
}
