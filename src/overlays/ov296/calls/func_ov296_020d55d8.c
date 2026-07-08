extern void *func_0203d15c(int size);
extern void OS_SPrintf(void *buffer, void *format);
extern int func_ov107_020c9c24(void *name);
extern void func_ov107_020c6624(void *obj, int arg);
extern int data_ov296_020d6160;
extern void func_ov296_020d5664(void *obj);

void *func_ov296_020d55d8(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = func_0203d15c(0x394);

    *(signed char *)((int)obj + 0x19c) = 0x70;
    OS_SPrintf(name, &data_ov296_020d6160);
    *(int *)((int)obj + 0x1a4) = func_ov107_020c9c24(name);
    *(void **)((int)obj + 0x18c) = func_ov296_020d5664;
    func_ov107_020c6624(obj, arg);
    return obj;
}
