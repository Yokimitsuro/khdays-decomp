extern void *func_0203d15c(int size);
extern void OS_SPrintf(void *buffer, void *format);
extern int func_ov107_020c9c24(void *name);
extern void func_ov107_020c6624(void *obj, int arg);
extern int data_ov281_020ce480;
extern void func_ov281_020cbfc4(void *obj);

void *func_ov281_020cbf38(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = func_0203d15c(0x3e8);

    *(signed char *)((int)obj + 0x19c) = 0x66;
    OS_SPrintf(name, &data_ov281_020ce480);
    *(int *)((int)obj + 0x1a4) = func_ov107_020c9c24(name);
    *(void **)((int)obj + 0x18c) = func_ov281_020cbfc4;
    func_ov107_020c6624(obj, arg);
    return obj;
}
