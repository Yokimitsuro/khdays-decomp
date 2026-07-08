extern int data_ov287_020d16e0;
extern void OS_SPrintf(void *buffer, void *format);
extern void *func_0203d15c(int size);
extern void func_ov107_020c6624(void *obj, int arg);
extern int func_ov107_020c9c24(void *name);
extern void func_ov287_020cfc04(void *obj);

void *func_ov287_020cfb78(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = func_0203d15c(0x3d0);

    *(signed char *)((int)obj + 0x19c) = 0x6b;
    OS_SPrintf(name, &data_ov287_020d16e0);
    *(int *)((int)obj + 0x1a4) = func_ov107_020c9c24(name);
    *(void **)((int)obj + 0x18c) = func_ov287_020cfc04;
    func_ov107_020c6624(obj, arg);
    return obj;
}
